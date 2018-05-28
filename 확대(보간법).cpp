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
int fnResizeImg(PGMImage *img_org, PGMImage *img_new, double n);
int fnInterpolate(PGMImage *img);


int main(int argc, char** argv)
{
	PGMImage	img_org;
	PGMImage	img_new;

	
	if(argc != 2){
		fprintf(stderr, "사용법 : %s <filename>\n", argv[0]);
		return -1;
	}


	if(fnReadPGM(argv[1], &img_org) != TRUE){
		return -1;
	}

	if(fnResizeImg(&img_org, &img_new, 1.3) != TRUE){
		return -1;
	}

	if(fnInterpolate(&img_new) != TRUE){
		return -1;
	}


	// <-- 결과 확인은 파일로 대체
	if(fnWritePGM("E:\\test\\result.pgm", &img_new) == TRUE){
		printf("파일 저장완료!\n");
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
		fprintf(stderr, "fnReadPGM 호출 에러\n");
		return FALSE;
	}
	
	fp = fopen(fileNm, "rb");	// binary mode
	if(fp == NULL){
		fprintf(stderr, "파일을 열 수 없습니다 : %s\n", fileNm);
		return FALSE;
	}

	fscanf(fp, "%c%c\n", &img->M, &img->N);	// 매직넘버 읽기

	if(img->M != 'P' || img->N != '5'){
		fprintf(stderr, "PGM 이미지 포멧이 아닙니다 : %c%c\n", img->M, img->N);
		return FALSE;
	}

	fscanf(fp, "%d %d\n", &img->width, &img->height);	// 가로, 세로 읽기
	fscanf(fp, "%d\n"   , &img->max                );	// 최대명암도 값

	if(img->max != 255){
		fprintf(stderr, "올바른 이미지 포멧이 아닙니다.\n");
		return FALSE;
	}


	// <-- 메모리 할당
	img->pixels = (unsigned char**)calloc(img->height, sizeof(unsigned char*));

	for(int i=0; i<img->height; i++){
		img->pixels[i] = (unsigned char*)calloc(img->width, sizeof(unsigned char));
	}
	// -->


	// <-- pgm 파일로부터 픽셀값을 읽어서 할당한 메모리에 load
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			fread(&img->pixels[i][j], sizeof(unsigned char), 1, fp);
		}
	}
	// -->


	fclose(fp);	// 더 이상 사용하지 않는 파일을 닫아 줌

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
		fprintf(stderr, "파일 생성에 실패하였습니다.\n");
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

int fnResizeImg(PGMImage *img_org, PGMImage *img_new, double n)
{
	int new_height = img_org->height * n;
	int new_width  = img_org->width  * n;
	int new_x;
	int new_y;	
	


	// 헤더값 복사
	img_new->M		= img_org->M;
	img_new->N		= img_org->N;
	img_new->width	= new_width;
	img_new->height = new_height;
	img_new->max	= img_org->max;

	//	*img_new = *img_org;	위 코드는 이런식으로 간단하게 할 수도 있음



	// <-- 메모리 할당 - 새로 생성될 이미지의 크기에 따라
	img_new->pixels = (unsigned char**)calloc(new_height, sizeof(unsigned char*));

	for(int i=0; i<new_height; i++){
		img_new->pixels[i] = (unsigned char*)calloc(new_width, sizeof(unsigned char));
	}
	// -->


	
	// <-- 배경색으로 초기화
	for(int i=0; i<img_new->height; i++){
		for(int j=0; j<img_new->width; j++){
			img_new->pixels[i][j] = 0;	// 0: 검정색
		}
	}
	// -->



	// <-- 리사이즈(확대, 축소)
	for(int i=0; i<img_org->height; i++){
		new_y = ceil(i * n);


		if(new_y >= img_new->height){
			new_y = img_new->height - 1;
		}

		
		for(int j=0; j<img_org->width; j++){
			new_x = ceil(j * n);

			if(new_x >= img_new->width){
				new_x = img_new->width - 1;
			}

			img_new->pixels[new_y][new_x] = img_org->pixels[i][j];
		}
	}
	// -->


	return TRUE;
}

int fnInterpolate(PGMImage *img)
{
	int pre_pixval = 0;

	// → 방향으로 진행
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			if(img->pixels[i][j] == 0 && pre_pixval != 0){
				img->pixels[i][j] = pre_pixval;
			}

			pre_pixval = img->pixels[i][j];
		}

		pre_pixval = 0;
	}


	// ↓ 방향으로 진행
	for(int m=0; m<img->width; m++){
		for(int n=0; n<img->height; n++){
			if(img->pixels[n][m] == 0 && pre_pixval != 0){
				img->pixels[n][m] = pre_pixval;
			}

			pre_pixval = img->pixels[n][m];
		}

		pre_pixval = 0;
	}


	return TRUE;
}