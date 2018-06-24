#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void sampling(int ,int ,double* );
void fourier(int ,double* ,double* );
void output_sample(int ,double* );
void output_fourier(int ,double* );

int main()
{
	int num,winlen;

	printf("出席番号を入力してください。");
	scanf("%d",&num);
	printf("窓長を入力してください。([ms]単位)");
	scanf("%d",&winlen);
	
	double date[winlen],res[winlen];
	
	sampling(num,winlen,date);
	output_sample(winlen,date);
	fourier(winlen,date,res);
	output_fourier(winlen,res);
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

void output_sample(int winlen_ous,double sam_ous[winlen_ous])
{
	FILE *fp;
	int i = (int)log10(winlen_ous)+1;
	char su[13+i];
	sprintf(su,"sample_%d.dat",winlen_ous);
	fp = fopen(su,"w");
	
	for(int i=0;i<winlen_ous;i++)
	{
		fprintf(fp,"%.3f	%.3f\n",(double)i,sam_ous[i]);
	}
	
	fclose(fp);
	
	
	FILE *gp;
	
	gp = popen("gnuplot -persist","w");
	fprintf(gp,"plot \"sample_%d.dat\" w lp \n",winlen_ous);
	pclose(gp);
}

void output_fourier(int winlen_ouf,double res_ouf[winlen_ouf])
{
	FILE *fp;
	int i = (int)log10(winlen_ouf)+1;
	char su[13+i];
	sprintf(su,"fourier_%d.dat",winlen_ouf);
	fp = fopen(su,"w");
	
	for(int i=0;i<winlen_ouf;i++)
	{
		fprintf(fp,"%.3f	%.3f\n",1000.0/(double)winlen_ouf*(double)i,res_ouf[i]);
	}
	
	fclose(fp);
	
	
	FILE *gp;
	
	gp = popen("gnuplot -persist","w");
	fprintf(gp,"plot \"fourier_%d.dat\" w lp \n",winlen_ouf);
	pclose(gp);
	
}
