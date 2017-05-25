#include <iostream>
#include <string>
#include <libfreenect2/libfreenect2.hpp>

#include <sys/ioctl.h>
#include <unistd.h>

#ifndef ASCII_VIEWER_H
#define ASCII_VIEWER_H



class Ascii_Viewer
{
  private:
    void ClearScreen();

    //Better to quantize data in separate loop/function
    //so the print frame will be smoother
    char** Quantize(const float *data, int height, int width);
    void getwinsize();
    unsigned short window_width;
    unsigned short window_height;
    uint32_t lastframe;
    void echo_frame_attributes(const libfreenect2::Frame *frame);

  public:
    Ascii_Viewer();
    //~Ascii_Viewer();
    void Display(const libfreenect2::Frame *frame);

};

#endif
/*

Ascii_Viewer::Ascii_Viewer()
{
  getwinsize();
  lastframe = 0;
}


void Ascii_Viewer::getwinsize()
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  window_width = w.ws_col;
  window_height = w.ws_row;
}

void Ascii_Viewer::ClearScreen()
{
  std::cout << std::string(window_height, '\n');
}


void Ascii_Viewer::echo_frame_attributes(const libfreenect2::Frame *frame)
{
  //const float *data = (float*)frame->data;

  std::cout << std::endl;
  std::cout << frame->width << std::endl;
  std::cout << frame->height << std::endl;
  std::cout << frame->bytes_per_pixel << std::endl;
  std::cout << frame->timestamp << std::endl;
  std::cout << frame->sequence << std::endl;
  std::cout << frame->exposure << std::endl;
  std::cout << frame->gain << std::endl;
  std::cout << frame->gamma << std::endl;
  std::cout << frame->status << std::endl;
  std::cout << frame->format << std::endl;;
  std::cout << std::endl;
}

void Ascii_Viewer::Display(const libfreenect2::Frame *frame)
{

  if((frame->timestamp-lastframe) < 1000)
  {
    return;
  }
  else if(frame->status != 0)
  {
    return;
  }
  else
  {
    lastframe = frame->timestamp;
  }

  const float *data = (float*)frame->data;

  const size_t frame_width = frame->width;
  const size_t frame_height = frame->height;
  char** chardata = Quantize(data, frame_height, frame_width);

  int horizontal_step_size = frame_width / window_width;
  int vertical_step_size = frame_height / window_height;

  //int has no decimals, let's round up
  horizontal_step_size++;
  vertical_step_size++;
  int i = 0;
  int j = 0;

  ClearScreen();
  for(i = 0; i < frame_height; i += vertical_step_size)
  {
    for(j = 0; j < frame_width; j += horizontal_step_size)
    {
      std::cout << chardata[i][j];
      //std::cout << "#";
    }
    std::cout << std::endl;
  }

  
  for (i=0; i < frame_height; i++)
  {
    delete [] chardata[i];
  }
  delete [] chardata;
  
}


char** Ascii_Viewer::Quantize(const float *data, int height, int width)
{

  float pixel;
  int ipixel;

  char** frame = '\0';
  frame = new char*[height];

  for (int i = 0; i < height; i++)
  {
    frame[i] = new char[width];

    for (int j = 0; j < width; j++)
    {
      pixel = data[i*width + j];
      pixel = pixel / 450;
      ipixel = static_cast<int>(pixel);

      switch(ipixel) 
      {
        case 0: 
          frame[i][j] = ' ';
          break;
        case 1: 
          frame[i][j] = '.';
          break;
        case 2: 
          frame[i][j] = ':';
          break;
        case 3: 
          frame[i][j] = '-';
          break;
        case 4: 
          frame[i][j] = '=';
          break;
        case 5: 
          frame[i][j] = '+';
          break;
        case 6: 
          frame[i][j] = '*';
          break;
        case 7: 
          frame[i][j] = '#';
          break;
        case 8: 
          frame[i][j] = '%';
          break;
        case 9: 
          frame[i][j] = '@';
          break;
        default: 
          std::cout << "Should never happen";
      }
    }
  }

  return frame;
}

  for(int i = 0; i < frame_height; i += vertical_step_size)
  {
    for(int j = 0; j < frame_width; j += horizontal_step_size)
    {
      pixel = data[i*frame_width + j];
      pixel = pixel / 450;
      ipixel = static_cast<int>(pixel);

      switch(ipixel) 
      {
        case 0: 
          std::cout << " ";
          break;
        case 1: 
          std::cout << ".";
          break;
        case 2: 
          std::cout << ":";
          break;
        case 3: 
          std::cout << "-";
          break;
        case 4: 
          std::cout << "=";
          break;
        case 5: 
          std::cout << "+";
          break;
        case 6: 
          std::cout << "*";
          break;
        case 7: 
          std::cout << "#";
          break;
        case 8: 
          std::cout << "%";
          break;
        case 9: 
          std::cout << "@";
          break;
        default: 
          std::cout << "Should never happen";
      }

    }
    std::cout << std::endl;
  }
  */






/*
void print_raw_rgb_frame(const libfreenect2::Frame *frame)
{

  ClearScreen();

  const unsigned int *data = (unsigned int*)frame->data;
  const size_t width = frame->width;
  const size_t height = frame->height;

  w terminal_window = getwinsize();
  //std::cout << terminal_window.ws_row << std::endl;
  //std::cout << terminal_window.ws_col << std::endl;

  for(int i = 0; i < terminal_window.ws_row-10; i++)
  {
    for(int j = 0; j < terminal_window.ws_col-10; j++)
    {
      unsigned int pixel = data[i*width + j];
      int R = pixel & 0xFF;

      int bin = R >> 5;

      switch(bin) 
      {
        case 0: 
          std::cout << ".";
          break;
        case 1: 
          std::cout << ":";
          break;
        case 2: 
          std::cout << "=";
          break;
        case 3: 
          std::cout << "+";
          break;
        case 4: 
          std::cout << "x";
          break;
        case 5: 
          std::cout << "#";
          break;
        case 6: 
          std::cout << "%";
          break;
        case 7: 
          std::cout << "@";
          break;
        default: 
          std::cout << "Should never happen";
      }
      //std::cout << bin;

    }
    std::cout << std::endl;
  }



}
*/
