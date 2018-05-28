#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning(disable:4996)

#define TRUE	1
#define FALSE	0


typedef struct {
	char	M, N;		// �����ѹ�
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
		fprintf(stderr, "���� : %s <filename>\n", argv[0]);
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


	// <-- ��� Ȯ���� ���Ϸ� ��ü
	if(fnWritePGM("E:\\test\\result.pgm", &img_new) == TRUE){
		printf("���� ����Ϸ�!\n");
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
		fprintf(stderr, "fnReadPGM ȣ�� ����\n");
		return FALSE;
	}
	
	fp = fopen(fileNm, "rb");	// binary mode
	if(fp == NULL){
		fprintf(stderr, "������ �� �� �����ϴ� : %s\n", fileNm);
		return FALSE;
	}

	fscanf(fp, "%c%c\n", &img->M, &img->N);	// �����ѹ� �б�

	if(img->M != 'P' || img->N != '5'){
		fprintf(stderr, "PGM �̹��� ������ �ƴմϴ� : %c%c\n", img->M, img->N);
		return FALSE;
	}

	fscanf(fp, "%d %d\n", &img->width, &img->height);	// ����, ���� �б�
	fscanf(fp, "%d\n"   , &img->max                );	// �ִ��ϵ� ��

	if(img->max != 255){
		fprintf(stderr, "�ùٸ� �̹��� ������ �ƴմϴ�.\n");
		return FALSE;
	}


	// <-- �޸� �Ҵ�
	img->pixels = (unsigned char**)calloc(img->height, sizeof(unsigned char*));

	for(int i=0; i<img->height; i++){
		img->pixels[i] = (unsigned char*)calloc(img->width, sizeof(unsigned char));
	}
	// -->


	// <-- pgm ���Ϸκ��� �ȼ����� �о �Ҵ��� �޸𸮿� load
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			fread(&img->pixels[i][j], sizeof(unsigned char), 1, fp);
		}
	}
	// -->


	fclose(fp);	// �� �̻� ������� �ʴ� ������ �ݾ� ��

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
		fprintf(stderr, "���� ������ �����Ͽ����ϴ�.\n");
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
	


	// ����� ����
	img_new->M		= img_org->M;
	img_new->N		= img_org->N;
	img_new->width	= new_width;
	img_new->height = new_height;
	img_new->max	= img_org->max;

	//	*img_new = *img_org;	�� �ڵ�� �̷������� �����ϰ� �� ���� ����



	// <-- �޸� �Ҵ� - ���� ������ �̹����� ũ�⿡ ����
	img_new->pixels = (unsigned char**)calloc(new_height, sizeof(unsigned char*));

	for(int i=0; i<new_height; i++){
		img_new->pixels[i] = (unsigned char*)calloc(new_width, sizeof(unsigned char));
	}
	// -->


	
	// <-- �������� �ʱ�ȭ
	for(int i=0; i<img_new->height; i++){
		for(int j=0; j<img_new->width; j++){
			img_new->pixels[i][j] = 0;	// 0: ������
		}
	}
	// -->



	// <-- ��������(Ȯ��, ���)
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

	// �� �������� ����
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			if(img->pixels[i][j] == 0 && pre_pixval != 0){
				img->pixels[i][j] = pre_pixval;
			}

			pre_pixval = img->pixels[i][j];
		}

		pre_pixval = 0;
	}


	// �� �������� ����
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