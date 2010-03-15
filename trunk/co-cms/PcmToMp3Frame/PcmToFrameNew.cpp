// LAME test program
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
// формальности соблюдены

#include "lame.h"
#include <wchar.h>
#include <stdlib.h>
#include "AS3.h"
#include <stdio.h>
#include <string.h>


//Класс для генерации двух массивов-каналов с сырыми PCM данными
class PcmGenerator
{
  float* m_buffer_ch0;
  float* m_buffer_ch1;
  int m_size;
  float m_a;
  float m_b;

  double random()
  {
    int const range_max = 32768;
    int const range_min = -32767;
    return (double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min;
  }
public:

  explicit PcmGenerator(int size)
  {    
    m_size = size >= 0 ? size : 0;
    m_buffer_ch0 = new float [m_size];
    m_buffer_ch1 = new float [m_size];
    m_a = 0;
    m_b = 0;
    advance(0);
  }

  ~PcmGenerator()
  {
    delete[] m_buffer_ch0;
    delete[] m_buffer_ch1;
  }

  float const* ch0() const 
  { 
	return m_buffer_ch0; 
  }
  float const* ch1() const 
  { 
	return m_buffer_ch1; 
  }

  void advance( int x ) 
  {
    float a = m_a;
    float b = m_b;
    for (int i = 0; i < m_size; ++i) 
	{
      a += 10;
      if (a > 32768) a = random();
      b -= 10;
      if (b < -32767) b = random();
      m_buffer_ch0[i] = a;
      m_buffer_ch1[i] = b;
    }
    m_a = a;
    m_b = b;
  }
};


//Класс для работы со стандартными функциями Лейма
class Lame
{
  lame_t m_gf;
  bool m_init_params_called;
  
  void ensureInitialized() {
    if (isOpen()) 
	{
      if (!m_init_params_called) 
	  {
        m_init_params_called = true;
        lame_init_params(m_gf);
      }
    }
  }

public:

  Lame()
    : m_gf( lame_init() ) 
    , m_init_params_called( false )
  {}

  ~Lame()
  {
    close();
  }

  void close() 
  {
    if (isOpen()) 
	{
      lame_close(m_gf);
      m_gf = 0;
    }
  }

  bool isOpen() const 
  {
    return m_gf != 0;
  }

  operator lame_t () 
  {
    return m_gf;
  }
  operator lame_t () const 
  {
    return m_gf;
  }

  void setInSamplerate( int rate ) 
  {
    lame_set_in_samplerate(m_gf, rate);
  }

  void setOutSamplerate( int rate ) 
  {
    lame_set_out_samplerate(m_gf, rate);
  }

  void setNumChannels( int num_channel ) 
  {
    lame_set_num_channels(m_gf, num_channel);
  }

  int encode(float const* ch0, float const* ch1, int n_in, unsigned char* out_buffer, int m_out_free) 
  {
    ensureInitialized();
    return lame_encode_buffer_float(m_gf, ch0, ch1, n_in, out_buffer, m_out_free);
  }

  int flush(unsigned char* out_buffer, int m_out_free) 
  {
    ensureInitialized();
    return lame_encode_flush(m_gf, out_buffer, m_out_free);
  }

  int getLameTag(unsigned char* out_buffer, int m_out_free) 
  {
    ensureInitialized();
    return lame_get_lametag_frame(m_gf, out_buffer, m_out_free);
  }

};


// Лейм предполагает кодирование данных сначала в массив, 
// после уже на усмотрение программиста, 
// в этой программе  массив пишется в выходной файл 
// Этот класс для работы с таким массивом
class OutBuffer
{
  unsigned char* m_data;
  int m_size;
  int m_used;

public:
  
  OutBuffer()
  {
    m_size = 1000 * 1000;
    m_data = new unsigned char[ m_size ];
    m_used = 0;
  }

  ~OutBuffer() 
  {
    delete[] m_data;
  }

  void advance( int i ) 
  {
    m_used += i;
  }

  int used() const 
  {
    return m_used;
  }

  int unused() const 
  {
    return m_size - m_used;
  }

  unsigned char* current() { return m_data + m_used; }
  unsigned char* begin()   { return m_data; }
};

// а это главная здесь функция, пока она скудна аргументами, 
// но когда будет работать, добавлю все необходимое
static AS3_Val generateFrames(void* self, AS3_Val args)
{
	
	long fileSize;
	char * buffer;	
	char* fileName = NULL;
	AS3_ArrayValue(args, "StrType", &fileName);
	
	if(fileName == NULL)
	{
		char* nullString = "null";
		return AS3_String(nullString);
	}
	
  // пока все эти параметры задаем так ( хотя бы они точно пойдут как параметры generateFrames) 
  int const chunk     = 1152;
  int ChannelNumber   = 2;
  int SampleRate      = 44100;
  size_t n            = 56;
  
  FILE *m_file_handle;  
  m_file_handle = fopen(fileName, "wb"); 
  
  PcmGenerator src(chunk);
  Lame lame;
  if (!lame.isOpen()) 
	return 0;

  OutBuffer mp3_stream_buffer;
  int rc = 0;

  lame.setInSamplerate(SampleRate);
  lame.setOutSamplerate(SampleRate);
  lame.setNumChannels(ChannelNumber);

  while (n > 0) 
  {    
    int const m = n < chunk ? n : chunk;
    if ( n < chunk ) 
		n = 0; 
	else 
		n -= chunk;
		
    rc = lame.encode(src.ch0(), src.ch1(), m, mp3_stream_buffer.current(), mp3_stream_buffer.unused());
    if (rc < 0) 
		return 0;
		
    mp3_stream_buffer.advance( rc ); // увеличиваем число использованных байт на 'rc'
    src.advance(m);                  // заполняем данными ch0 и ch1
  }

  rc = lame.flush(mp3_stream_buffer.current(), mp3_stream_buffer.unused());  // сколько байт осталось до нормального размера мп3 фрейма
 
  if (rc < 0) return 0;

  mp3_stream_buffer.advance( rc );  // увеличиваем число использованных байт на 'rc'

  int lametag_size = lame.getLameTag(0,0);
  wprintf(L"lametag_size=%d\n",lametag_size);

  rc = lame.getLameTag(mp3_stream_buffer.begin(), lametag_size);
 
  if (rc < 0) return 0;

  fwrite(mp3_stream_buffer.begin(), 1, mp3_stream_buffer.used(), m_file_handle);
  lame.close();
 
  


  fseek (m_file_handle, 0, SEEK_END);
  fileSize = ftell(m_file_handle);
  rewind(m_file_handle);
  buffer = (char*) malloc(sizeof(char)*fileSize);
 
 
  //fread(buffer, 1, fileSize, m_file_handle);
	
  fclose( m_file_handle );
  
  free (buffer);
  	
 return AS3_String((char*)buffer);
}


// мейн уже полностью Олега, (вместе с комментариями)
int main()
{
	//define the methods exposed to ActionScript
	//typed as an ActionScript Function instance
	AS3_Val generateFramesMethod = AS3_Function( NULL, generateFrames );

	// construct an object that holds references to the functions
	AS3_Val result = AS3_Object( "generateFrames: AS3ValType", generateFramesMethod );

	// Release
	AS3_Release( generateFramesMethod );

	// notify that we initialized -- THIS DOES NOT RETURN!
	AS3_LibInit( result );

	// should never get here!
	return 0;
}