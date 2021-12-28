#ifndef CORE_TGA
#define CORE_TGA

#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <cmath>

// set new packing alignment value
#pragma pack(push,1)
struct tga_header
{
    char idlength;
    char colormaptype;
    char datatypecode;
    short colormaporigin;
    short colormaplength;
    char colormapdepth;
    short x_origin;
    short y_origin;
    short width;
    short height;
    char  bitsperpixel;
    char  imagedescriptor;
};
#pragma pack(pop)

struct tga_color
{
	unsigned char bgra[4];
	unsigned char bytespp;

	tga_color() : bgra(), bytespp(1) { for(int i = 0; i < 4; i++) bgra[i] = 0; }

	tga_color(unsigned char R, unsigned char G, unsigned char B, unsigned char A=255) : bgra(), bytespp(4)
	{
		bgra[0] = B;
        bgra[1] = G;
        bgra[2] = R;
        bgra[3] = A;
	}

	tga_color(unsigned char v) : bgra(), bytespp(1)
	{
		bgra[0] = v;
		for(int i = 1; i < 4; i++) 
			bgra[i] = 0;
	}

	tga_color(const unsigned char *p, unsigned char bpp) : bgra(), bytespp(bpp)
	{
		for (int i = 0; i < (int)bpp; ++i)
		{
			bgra[i] = p[i];
		}
		for (int i = bpp; i < 4; ++i)
		{
			bgra[i] = 0;
		}
	}

	unsigned char& operator[](const int i) { return bgra[i]; }

	tga_color operator *(double intensity) const
	{
		tga_color res = *this;
		intensity = (intensity > 1. ? 1. : (intensity < 0. ? 0. : intensity));
		for (int i = 0; i < 4; ++i)
		{
			res.bgra[i] = bgra[i] * intensity;
		}
		return res;
	}
};

class tga
{
protected:
	unsigned char* data;
	int width;
	int height;
	int bytespp;

	bool load_rle_data(std::ifstream &in)
	{
		unsigned long pixelcount = width * height;
    	unsigned long currentpixel = 0;
    	unsigned long currentbyte = 0;

    	tga_color colorbuffer;

    	do
    	{
    		unsigned char chunkheader = 0;
    		chunkheader = in.get();
    		if (!in.good())
    		{
            	std::cerr << "an error occured while reading the data\n";
            	return false;
        	}
        	if (chunkheader < 128)
        	{
            	chunkheader++;
            	for (int i = 0; i < chunkheader; i++)
            	{
                	in.read((char *)colorbuffer.bgra, bytespp);
                	if (!in.good())
                	{
                    	std::cerr << "an error occured while reading the header\n";
                    	return false;
                	}
                	for (int t = 0; t < bytespp; t++)
                	{
                		data[currentbyte++] = colorbuffer.bgra[t];
                	}
                	currentpixel++;
                	if (currentpixel > pixelcount)
                	{
                    	std::cerr << "Too many pixels read\n";
                    	return false;
                	}
            	}
        	}
        	else 
        	{
            	chunkheader -= 127;
            	in.read((char *)colorbuffer.bgra, bytespp);
            	if (!in.good())
            	{
                	std::cerr << "an error occured while reading the header\n";
                	return false;
            	}
            	for (int i=0; i < chunkheader; i++)
            	{
                	for (int t=0; t < bytespp; t++)
                	{
                    	data[currentbyte++] = colorbuffer.bgra[t];
                    }
                	currentpixel++;
                	if (currentpixel > pixelcount)
                	{
                    	std::cerr << "Too many pixels read\n";
                    	return false;
                	}
            	}
        	}
    	}
    	while (currentpixel < pixelcount);

		return true;
	}

public:
	enum format { GRAYSCALE = 1, RGB = 3, RGBA = 4 };

	tga() : data(nullptr), width(0), height(0), bytespp(0) {}
	
	tga(int w, int h, int bpp) : data(nullptr), width(w), height(h), bytespp(bpp)
	{
		unsigned long nbytes = width * height * bytespp;
		data = new unsigned char[nbytes];
		memset(data, 0, nbytes);
	}

	~tga() { if(data) delete [] data; }

	tga& operator=(const tga &img)
	{
		if (this != &img)
		{
			if (data) delete [] data;
			width = img.width;
			height = img.height;
			bytespp = img.bytespp;
			unsigned long nbytes = width*height*bytespp;
        	data = new unsigned char[nbytes];
        	memcpy(data, img.data, nbytes);
		}
		return *this;
	}

	bool read_tga_file(const char *filename)
	{
		if(data) delete [] data;

		data = nullptr;
		std::ifstream in;
		in.open(filename, std::ios::binary);

		if (!in.is_open())
		{
			std::cerr << "can't open file: " << filename << "\n";
			in.close();
			return false;
		}

		tga_header header;
		in.read((char *)&header, sizeof(header));
		if (!in.good())
		{
			in.close();
			std::cerr << "an error occured while reading the header\n";
			return false;
		}

		width = header.width;
		height = header.height;
		bytespp = header.bitsperpixel>>3;
		if (width <= 0 || height <= 0 || (bytespp != GRAYSCALE && bytespp != RGB && bytespp != RGBA))
		{
			in.close();
			std::cerr << "bad bpp (or width/height) value\n";
			return false;
		}
		unsigned long nbytes = bytespp * width * height;
		data = new unsigned char[nbytes];

		if (3 == header.datatypecode || 2 == header.datatypecode)
		{
        	in.read((char *)data, nbytes);
        	if (!in.good())
        	{
            	in.close();
            	std::cerr << "an error occured while reading the data\n";
            	return false;
        	}
    	}
    	else if (10 == header.datatypecode || 11 == header.datatypecode)
    	{
        	if (!load_rle_data(in))
        	{
            	in.close();
            	std::cerr << "an error occured while reading the data\n";
            	return false;
        	}
    	}
    	else
    	{
        	in.close();
        	std::cerr << "unknown file format " << (int)header.datatypecode << "\n";
        	return false;
    	}

    	if (!(header.imagedescriptor & 0x20))
    	{
        	flip_vertically();
    	}
    	if (header.imagedescriptor & 0x10)
    	{
        	flip_horizontally();
    	}
    	std::cerr << width << "x" << height << "/" << bytespp*8 << "\n";
    	in.close();
    	return true;
	}

	tga_color get(int x, int y)
	{
		if (!data || x < 0 || y < 0 || x >= width || y >= height)
		{
        	return tga_color();
    	}
    	return tga_color(data + (x + y * width) * bytespp, bytespp);
	}

	bool set(int x, int y, const tga_color &c)
	{
		if (!data || x < 0 || y < 0 || x >= width || y >= height) return false;
    	memcpy(data + (x + y * width) * bytespp, c.bgra, bytespp);
    	return true;
	}

	bool flip_horizontally()
	{
		if(!data) return false;
		int half = width>>1;
    	for (int i=0; i < half; i++)
    	{
        	for (int j=0; j < height; j++)
        	{
            	tga_color c1 = get(i, j);
            	tga_color c2 = get(width-1-i, j);
            	set(i, j, c2);
            	set(width - 1 -i, j, c1);
        	}
    	}
   		return true;
	}

	bool flip_vertically()
	{
		if(!data) return false;
		unsigned long bytes_per_line = width * bytespp;
		unsigned char *line = new unsigned char[bytes_per_line];
		int half = height>>1;
		for (int i = 0; i < half; ++i)
		{
			unsigned long l1 = i * bytes_per_line;
			unsigned long l2 = (height - 1 - i) * bytes_per_line;
			memmove((void *)line, (void *)(data + l1), bytes_per_line);
        	memmove((void *)(data + l1), (void *)(data + l2), bytes_per_line);
        	memmove((void *)(data + l2), (void *)line, bytes_per_line);
		}
		delete [] line;
    	return true;
	}

	unsigned char *buffer() { return data; }

	void clear() { memset((void *)data, 0, width * height * bytespp); }

	int get_width() { return width; }

	int get_height() { return height; }
};

#endif // CORE_TGA