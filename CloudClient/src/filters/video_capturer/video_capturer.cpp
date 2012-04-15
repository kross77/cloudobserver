#include "video_capturer.h"

using namespace ffmpeg;

video_capturer::video_capturer(int video_width, int video_height, int video_frame_rate)
{
	this->width = video_width;
	this->height = video_height;
	this->frame_rate = video_frame_rate;

	this->captured_frame = NULL;
	this->resized_frame = NULL;
	this->ready_resized_frame = NULL;

	this->frame = avcodec_alloc_frame();
	uint8_t* frame_buffer = (uint8_t*)av_mallocz(avpicture_get_size(PIX_FMT_BGR24, this->width, this->height));
	avpicture_fill((AVPicture*)frame, frame_buffer, PIX_FMT_BGR24, this->width, this->height);

	this->ready_frame = avcodec_alloc_frame();
	uint8_t* ready_frame_buffer = (uint8_t*)av_mallocz(avpicture_get_size(PIX_FMT_BGR24, this->width, this->height));
	avpicture_fill((AVPicture*)ready_frame, ready_frame_buffer, PIX_FMT_BGR24, this->width, this->height);

	this->capture_device = NULL;

	this->line_segment_detector_block = NULL;
	this->video_player_block = NULL;
	this->video_encoder_block = NULL;

	this->set_capture_device(0);
}

video_capturer::~video_capturer()
{
	cvReleaseCapture(&this->capture_device);

	av_free(this->frame->data[0]);
	av_free(this->frame);

	av_free(this->ready_frame->data[0]);
	av_free(this->ready_frame);
}

void video_capturer::connect(line_segment_detector* line_segment_detector_block)
{
	this->line_segment_detector_block = line_segment_detector_block;
}

void video_capturer::connect(video_player* video_player_block)
{
	this->video_player_block = video_player_block;
}

void video_capturer::connect(video_encoder* video_encoder_block)
{
	this->video_encoder_block = video_encoder_block;
}

void video_capturer::disconnect()
{
	this->line_segment_detector_block = NULL;
	this->video_player_block = NULL;
	this->video_encoder_block = NULL;
}

void video_capturer::send()
{
	if (this->line_segment_detector_block != NULL)
		this->line_segment_detector_block->send(this->ready_resized_frame);
	if (this->video_encoder_block != NULL)
		this->video_encoder_block->send(this->ready_frame);
}

void video_capturer::start()
{
	this->capture_thread = boost::shared_ptr<boost::thread>(new boost::thread(&video_capturer::capture_loop, this));
}

void video_capturer::stop()
{
	this->capture_thread->interrupt();
}

void video_capturer::set_capture_device(int capture_device_index)
{
	if (this->capture_device != NULL)
	{
		cvReleaseCapture(&this->capture_device);
		this->capture_device = NULL;
	}

	// OpenCV doesn't provide the 'default' capture source, so we treat the zero (default) index just as the first capture device.
	// Any other index should be decremented as OpenCV counts the sources from 0.
	if (capture_device_index > 0)
		capture_device_index--;

	this->capture_device = cvCreateCameraCapture(capture_device_index);
	if (this->capture_device == NULL)
	{
		std::cout << "Video capturer: cannot initialize video capture device." << std::endl;
		throw internal_exception();
	}

	cvSetCaptureProperty(this->capture_device, CV_CAP_PROP_FRAME_WIDTH, this->width);
	cvSetCaptureProperty(this->capture_device, CV_CAP_PROP_FRAME_HEIGHT, this->height);
	cvSetCaptureProperty(this->capture_device, CV_CAP_PROP_FPS, this->frame_rate);

	this->captured_frame = cvQueryFrame(this->capture_device);
	this->resized_frame = cvCreateImage(cvSize(this->width, this->height), this->captured_frame->depth, this->captured_frame->nChannels);
	this->ready_resized_frame = cvCreateImage(cvSize(this->width, this->height), this->captured_frame->depth, this->captured_frame->nChannels);
}

std::vector<std::string> video_capturer::get_capture_devices()
{
	std::vector<std::string> capture_devices;

#ifdef WIN
	HRESULT hr;

	// Initialize the COM library.
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		std::cout << "Video capturer: failed to initialize the COM library." << std::endl;
		throw internal_exception();
	}

	// Create the System Device Enumerator.
	ICreateDevEnum* device_enumerator;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&device_enumerator));
	if (FAILED(hr))
	{
		std::cout << "Video capturer: failed to create the System Device Enumerator." << std::endl;
		throw internal_exception();
	}

	// Create an enumerator for the Video Input Device category.
	IEnumMoniker* enumerator;
	hr = device_enumerator->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &enumerator, 0);
	if (FAILED(hr))
	{
		std::cout << "Video capturer: failed to create an enumerator for the Video Input Device category." << std::endl;
		throw internal_exception();
	}
	
	// Release the System Device Enumerator.
	device_enumerator->Release();

	IMoniker* moniker = NULL;
	while (enumerator->Next(1, &moniker, NULL) == S_OK)
	{
		IPropertyBag* property_bag;
		hr = moniker->BindToStorage(0, 0, IID_PPV_ARGS(&property_bag));
		if (FAILED(hr))
		{
			moniker->Release();
			continue;
		}

		VARIANT var;
		VariantInit(&var);

		hr = property_bag->Read(L"Description", &var, 0);
		if (FAILED(hr))
			hr = property_bag->Read(L"FriendlyName", &var, 0);
		if (SUCCEEDED(hr))
		{
			capture_devices.push_back(std::string(bstr_t(var.bstrVal)));
			VariantClear(&var);
		}

		property_bag->Release();
		moniker->Release();
	}
#endif

#ifdef LIN
	int file_descriptor;
	int device_number = 0;
	std::ostringstream device;
	device << "/dev/video" << device_number;
	while ((file_descriptor = open(device.str().c_str(), O_RDONLY)) != -1)
	{
		struct v4l2_capability capability;
		memset(&capability, 0, sizeof(capability));
		ioctl(file_descriptor, VIDIOC_QUERYCAP, &capability);
		capture_devices.push_back(std::string((char*)capability.card));
		close(file_descriptor);

		device_number++;
		device.str("");
		device << "/dev/video" << device_number;
	}
#endif

#ifdef MAC
	// TODO: Rewrite using QTKit framework instead of QuickTime framework.
	// The latter is not available on 64-bit Mac OS X systems.
	/*ComponentResult result;

	// Find the sequence grabber.
	ComponentDescription sequence_grabber_description;
	sequence_grabber_description.componentType = SeqGrabComponentType;
	sequence_grabber_description.componentSubType = 0L;
	sequence_grabber_description.componentManufacturer = 'appl';
	sequence_grabber_description.componentFlags = 0L;
	sequence_grabber_description.componentFlagsMask = 0L;
	Component sequence_grabber_component = FindNextComponent(NULL, &sequence_grabber_description);
	if (!sequence_grabber_component)
	{
		std::cout << "Video capturer: failed to find the sequence grabber." << std::endl;
		throw internal_exception();
	}

	// Open the sequence grabber.
	SeqGrabComponent sequence_grabber = OpenComponent(sequence_grabber_component);
	if (!sequence_grabber)
	{
		std::cout << "Video capturer: failed to open the sequence grabber." << std::endl;
		throw internal_exception();
	}

	// Initialize the sequence grabber.
	result = SGInitialize(sequence_grabber);
	if (result != noErr)
	{
		std::cout << "Video capturer: failed to initialize the sequence grabber." << std::endl;
		throw internal_exception();
	}

	// Get a video channel.
	SGChannel video_channel;
	result = SGNewChannel(sequence_grabber, VideoMediaType, &video_channel);
	if (result != noErr)
	{
		std::cout << "Video capturer: failed to get a video channel." << std::endl;
		throw internal_exception();
	}

	// Get a device list.
	SGDeviceList device_list;
	SGGetChannelDeviceList(video_channel, sgDeviceListDontCheckAvailability | sgDeviceListIncludeInputs, &device_list);
	if (!device_list)
	{
		std::cout << "Video capturer: failed to get a device list." << std::endl;
		throw internal_exception();
	}

	// Dispose the video channel.
	SGDisposeChannel(sequence_grabber, video_channel);

	for (int device_index = 0; device_index < (*device_list)->count; ++device_index)
	{
		SGDeviceName device = (*device_list)->entry[device_index];
		if (device.inputs != NULL)
			for (int input_index = 0; input_index < (*device.inputs)->count; ++input_index)
			{
				SGDeviceInputName input = (*device.inputs)->entry[input_index];
				capture_devices.push_back(std::string((char*)input.name));
			}
	}

	SGDisposeDeviceList(sequence_grabber, device_list);
	SGRelease(sequence_grabber);*/
#endif

	return capture_devices;
}

void video_capturer::capture_loop()
{
	timer time;
	boost::posix_time::time_duration period(boost::posix_time::milliseconds(1000 / this->frame_rate));
	while (true)
	{
		time.restart();

		this->captured_frame = cvQueryFrame(this->capture_device);
		if (this->video_player_block != NULL)
			this->video_player_block->send(this->captured_frame);
		cvResize(this->captured_frame, this->resized_frame);

		IplImage* swap_resized_frame = this->ready_resized_frame;
		this->ready_resized_frame = this->resized_frame;
		this->resized_frame = swap_resized_frame;

		char* buffer = (char*)this->frame->data[0];
		for (int i = 0; i < this->resized_frame->imageSize; i += 3)
		{
			buffer[2] = this->resized_frame->imageData[i];
			buffer[1] = this->resized_frame->imageData[i + 1];
			buffer[0] = this->resized_frame->imageData[i + 2];
			buffer += 3;
		}

		AVFrame* swap_frame = this->ready_frame;
		this->ready_frame = this->frame;
		this->frame = swap_frame;

		boost::this_thread::sleep(period - time.elapsed());
	}
}
