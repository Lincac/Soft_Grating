#include"ppmimage.h"

PPMImage::PPMImage() : data(nullptr),width(0),height(0) {}

PPMImage::~PPMImage(){
	if(data) delete[] data;
}

PPMImage::PPMImage(const PPMImage& ppm){
	width = ppm.width;
	height = ppm.height;
	unsigned long nbytes = width * height * bytespp;
	data = new float[nbytes];
	memcpy(data,ppm.data,nbytes * sizeof(float)); 
}

PPMImage::PPMImage(const int w,const int h,float c) : width(w),height(h) {
	unsigned int nbytes = width * height * bytespp;
	data = new float[nbytes];
	std::fill(data,data + nbytes,c);
}

bool PPMImage::read_ppm_file(const char* filename){
	int w, h, channels;
    unsigned char* img = stbi_load("resource/texture/brickwall.jpg", &w, &h, &channels, STBI_rgb);
    if (!img) {
        std::cout << "Failed to load image!" << std::endl;
        return -1;
    }

	width = w;
	height = h;
	unsigned int nbytes = width * height * channels;
	data = new float[nbytes];

	for (int i = 0; i < w * h * channels; i++)
		data[i] = img[i];

	stbi_image_free(img);
	return true;
}

bool PPMImage::write_ppm_file(const char* filename) const{
	FILE* file = fopen(filename, "wb");
	(void)fprintf(file, "P6\n%d %d\n255\n", width, height);

	float *image = data;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {

			static unsigned char RGB[3]{};
			// RGB[0] = static_cast<unsigned char>(clamp(0,255,pow(*image,1 / 2.2) * 255)); image++;
			// RGB[1] = static_cast<unsigned char>(clamp(0,255,pow(*image,1 / 2.2) * 255)); image++;
			// RGB[2] = static_cast<unsigned char>(clamp(0,255,pow(*image,1 / 2.2) * 255)); image++;
			RGB[0] = static_cast<unsigned char>(*image); image++;
			RGB[1] = static_cast<unsigned char>(*image); image++;
			RGB[2] = static_cast<unsigned char>(*image); image++;
			fwrite(RGB, 1, 3, file);
		}
	}
	fclose(file);
	
	return true;
}

bool PPMImage::set(const int x, const int y, const PPMColor &c){
	if(!data || x<0 || y<0 || x>=width || y>=height){
		return false;
	}
	memcpy(data + (x + (height -1 - y) * width) * bytespp,c.raw,bytespp * sizeof(float));
	return true;
}

int PPMImage::get_width() const{
	return width;
}

int PPMImage::get_height() const {
	return height;
}

PPMColor PPMImage::get_color(int x,int y){
	if(!data || x >= width || x < 0 || y >= height || y < 0){
		return PPMColor();
	}
	PPMColor temp;
	memcpy(temp.raw,data + (x + (height - 1 - y) * width) * bytespp,bytespp * sizeof(float));
	return temp;
}


void PPMImage::clear(float d){
	if(data) {
		unsigned long bytes = width * height * bytespp;
		std::fill(data,data + bytes,d);
	}
}