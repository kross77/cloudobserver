
	typedef struct ntuple_list_s
	{
		unsigned int size;
		unsigned int max_size;
		unsigned int dim;
		double * values;
	} * ntuple_list;

	typedef struct image_char_s
	{
		unsigned char * data;
		unsigned int xsize,ysize;
	} * image_char;

	typedef struct image_int_s
	{
		int * data;
		unsigned int xsize,ysize;
	} * image_int;

	typedef struct image_double_s
	{
		double * data;
		unsigned int xsize,ysize;
	} * image_double;

	

	void free_ntuple_list(ntuple_list in);
	ntuple_list new_ntuple_list(unsigned int dim);

	void free_image_char(image_char i);
	image_char new_image_char(unsigned int xsize, unsigned int ysize);
	image_char new_image_char_ini( unsigned int xsize, unsigned int ysize,
		unsigned char fill_value );

	void free_image_int(image_int i);
	image_int new_image_int(unsigned int xsize, unsigned int ysize);
	image_int new_image_int_ini( unsigned int xsize, unsigned int ysize,
		int fill_value );

	void free_image_double(image_double i);
	image_double new_image_double(unsigned int xsize, unsigned int ysize);
	image_double new_image_double_ini( unsigned int xsize, unsigned int ysize,
		double fill_value );

	ntuple_list LineSegmentDetection( image_double image, double scale,
		double sigma_scale, double quant,
		double ang_th, double eps, double density_th,
		int n_bins, double max_grad,
		image_int * region );

	ntuple_list lsd_scale(image_double image, double scale);

	ntuple_list lsd(image_double image);
