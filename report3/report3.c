#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void sampling(int ,int ,double* );
void fourier(int ,double* ,double* );
void output(int ,double* );

int main()
{
	int num,winlen;

	printf("出席番号を入力してください。");
	scanf("%d",&num);
	printf("窓長を入力してください。([ms]単位)");
	scanf("%d",&winlen);
	
	double date[winlen],res[winlen];
	
	sampling(num,winlen,date);
	fourier(winlen,date,res);
	output(winlen,res);
	return 0;
}

void sampling(int num_sam,int winlen_sam,double date_sam[winlen_sam])	//南無阿弥陀仏
{
	for(int i=0;i<winlen_sam;i++)
	{
		date_sam[i] = sin(2.0*M_PI*(200.0+(double)num_sam)*(double)i/1000.0);
	}
}


void fourier(int winlen_fo,double date_fo[winlen_fo],double res_fo[winlen_fo])
{
	double re,im;
	re = im = 0;

	for(int i=0;i<winlen_fo;i++)	//t
	{
		for(int j=0;j<winlen_fo;j++)	//x
		{
			re = re + date_fo[j]*cos(-2.0*M_PI*(double)i*(double)j/(double)winlen_fo);
			im = im + date_fo[j]*sin(-2.0*M_PI*(double)i*(double)j/(double)winlen_fo);
		}
		
		re = re/winlen_fo;
		im = im/winlen_fo;
		res_fo[i] = sqrt(re*re+im*im);
	}
}


void output(int winlen_ou,double res_ou[winlen_ou])
{
	FILE *fp;
	int i = (int)log10(winlen_ou)+1;
	char su[13+i];
	sprintf(su,"fourier_%d.dat",winlen_ou);
	fp = fopen(su,"w");
	
	for(int i=0;i<winlen_ou;i++)
	{
		fprintf(fp,"%.3f	%.3f\n",1000.0/(double)winlen_ou*(double)i,res_ou[i]);
	}
	
	fclose(fp);
	
	/*
	FILE *gp;
	
	gp = popen("gnuplot -persist","w");
	fprintf(gp,"plot \"fourier_%d.dat\" w lp \n",winlen_ou);
	pclose(gp);
	*/
}