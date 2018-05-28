#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning(disable:4996)

#define TRUE	1
#define FALSE	0


typedef struct {
	char	M, N;		// 매직넘버
	int		width;
	int		height;
	int		max;
	unsigned char **pixels;
} PGMImage;


int fnReadPGM(char* fileNm, PGMImage* img);
void fnClosePGM(PGMImage* img);
int fnWritePGM(char* fileNm, PGMImage* img);
int fnRotateImg(PGMImage *img_org, PGMImage *img_new, double degree);
int fnInterpolate(PGMImage *img);


int main(int argc, char** argv)
{
	PGMImage	img_org;
	PGMImage	img_new;

	
	if(argc != 2){
		fprintf(stderr, "사용법: %s <filename>\n", argv[0]);
		return -1;
	}


	if(fnReadPGM(argv[1], &img_org) != TRUE){
		return -1;
	}

	if(fnRotateImg(&img_org, &img_new, 20.0) != TRUE){
		return -1;
	}

	if(fnInterpolate(&img_new) != TRUE){
		return -1;
	}


	// <-- 결과확인은파일로대체
	if(fnWritePGM("E:\\test\\result.pgm", &img_new) == TRUE){
		printf("파일저장완료!\n");
	}
	// -->

	fnClosePGM(&img_org);
	fnClosePGM(&img_new);

	return 0;
}

int fnReadPGM(char* fileNm, PGMImage* img)
{
	FILE* fp;

	if(fileNm == NULL){
		fprintf(stderr, "fnReadPGM 호출에러\n");
		return FALSE;
	}
	
	fp = fopen(fileNm, "rb");	// binary mode
	if(fp == NULL){
		fprintf(stderr, "파일을열수없습니다: %s\n", fileNm);
		return FALSE;
	}

	fscanf(fp, "%c%c\n", &img->M, &img->N);	// 매직넘버읽기

	if(img->M != 'P' || img->N != '5'){
		fprintf(stderr, "PGM 이미지포멧이아닙니다: %c%c\n", img->M, img->N);
		return FALSE;
	}

	fscanf(fp, "%d %d\n", &img->width, &img->height);	// 가로, 세로읽기
	fscanf(fp, "%d\n"   , &img->max                );	// 최대명암도값

	if(img->max != 255){
		fprintf(stderr, "올바른이미지포멧이아닙니다.\n");
		return FALSE;
	}


	// <-- 메모리할당
	img->pixels = (unsigned char**)calloc(img->height, sizeof(unsigned char*));

	for(int i=0; i<img->height; i++){
		img->pixels[i] = (unsigned char*)calloc(img->width, sizeof(unsigned char));
	}
	// -->


	// <-- pgm 파일로부터픽셀값을읽어서할당한메모리에load
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			fread(&img->pixels[i][j], sizeof(unsigned char), 1, fp);
		}
	}
	// -->


	fclose(fp);	// 더이상사용하지않는파일을닫아줌

	return TRUE;
}

void fnClosePGM(PGMImage* img)
{
	for(int i=0; i<img->height; i++){
		free(img->pixels[i]);
	}

	free(img->pixels);
}

int fnWritePGM(char* fileNm, PGMImage* img)
{
	FILE* fp;

	fp = fopen(fileNm, "w");
	if(fp == NULL){
		fprintf(stderr, "파일생성에실패하였습니다.\n");
		return FALSE;
	}

	fprintf(fp, "%c%c\n", 'P', '2');
	fprintf(fp, "%d %d\n" , img->width, img->height);
	fprintf(fp, "%d\n", 255);


	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){			
			fprintf(fp, "%d ", img->pixels[i][j]);
		}
	}

	fclose(fp);
	
	return TRUE;
}

int fnRotateImg(PGMImage *img_org, PGMImage *img_new, double degree)
{
	int center_x = img_org->width  / 2;
	int center_y = img_org->height / 2;
	int new_x;
	int new_y;
	double pi = 3.1415926535;
	double seta;
	

	// seta값계산
	seta = pi / (180.0 / degree);


	// 헤더값복사
	img_new->M		= img_org->M;
	img_new->N		= img_org->N;
	img_new->width	= img_org->width;
	img_new->height = img_org->height;
	img_new->max	= img_org->max;

	//	*img_new = *img_org;	위코드는이런식으로간단하게할수도있음



	// <-- 메모리할당- 새로생성될이미지의크기에따라
	img_new->pixels = (unsigned char**)calloc(img_org->height, sizeof(unsigned char*));

	for(int i=0; i<img_org->height; i++){
		img_new->pixels[i] = (unsigned char*)calloc(img_org->width, sizeof(unsigned char));
	}
	// -->


	
	// <-- 배경색으로초기화
	for(int i=0; i<img_new->height; i++){
		for(int j=0; j<img_new->width; j++){
			img_new->pixels[i][j] = 0;	// 0: 검정색
		}
	}
	// -->



	// <-- 회전
	for(int i=0; i<img_org->height; i++){
		for(int j=0; j<img_org->width; j++){
			new_x = (i-center_y) * sin(seta) + (j-center_x) * cos(seta) + center_x;
			new_y = (i-center_y) * cos(seta) - (j-center_x) * sin(seta) + center_y;
			
			if(new_x < 0 )					continue;
			if(new_x >= img_org->width)		continue;
			if(new_y < 0)					continue;
			if(new_y >= img_org->height)	continue;

			img_new->pixels[new_y][new_x] = img_org->pixels[i][j];
		}
	}
	// -->


	return TRUE;
}

int fnInterpolate(PGMImage *img)
{
	int left_pixval = 0;
	int right_pixval = 0;


	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			if(j == 0){
				right_pixval = img->pixels[i][j+1];
				left_pixval  = right_pixval;
			}
			else if(j == img->width - 1){
				left_pixval  = img->pixels[i][j-1];
				right_pixval = left_pixval;
			}
			else{
				left_pixval  = img->pixels[i][j-1];
				right_pixval = img->pixels[i][j+1];
			}
			

			if(img->pixels[i][j] == 0 && left_pixval != 0 && right_pixval != 0){
				img->pixels[i][j] = ( left_pixval + right_pixval ) / 2;
			}
		}
	}

	return TRUE;
}