#include<bits/stdc++.h>
//#include<set.h>
//#include<algorithm.h>
//#include<random.h>
using namespace std;
const float pi=3.14;
int N_iter;
/*
double fun(double u[])
{

	 double z=pow((1-u[0]),2)+100*pow((u[1]-u[0]*u[0]),2)+100*pow((u[2]-(u[1]*u[1])),2);
	return z;
}*/
//simplebounds function

void simplebounds(double *s, int  lb[], int ub[],int d){
	for(int i=0; i<d; ++i){

		if(s[i]<lb[i]) s[i] = lb[i];

		if(s[i]>ub[i]) s[i] = ub[i];

	}
}
//fitness function

double fun(double u[])
{
	double z=(u[0]*u[0])+(u[1]*u[1])+(u[2]*u[2]);
	return z;
}
double* Levy(int d)
{
	int i;
	float beta=1.5;
	double u[d];
	double v[d];
	//double step[d],l[d];
	double *step = new double[d];
	double sigma=pow((tgamma(1+beta)*sin(pi*beta/2)/(tgamma((1+beta)/2)*beta*pow(2,((beta-1)/2)))),(1/beta));
	for(i=0;i<d;i++)
	{
		u[i]=(rand())*sigma;
	}

	for(i=0;i<d;i++)
	{
		v[i]=rand();
	}

	for(i=0;i<d;i++)
	{
		step[i]=u[i]/pow(abs(v[i]),(1/beta));
		step[i]=0.01*step[i];
	}
	return step;
}

int main()
{
	int d=3,i,j,n,t;

	cout<<"enter value of n and  iterations"<<endl;
	// float para[2]={20,0.8};
	cin>>n>>N_iter;
	float p=0.8;
	double s[n][d];
	int lb[d];
	double sol[n][d];
	int ub[d];

	for(j=0;j<3;j++)
	{
		lb[j]=-2;
	}
	for(j=0;j<3;j++)
	{
		ub[j]=2;
	}
	double fitness[n],arr[d];
	cout<<"enter values"<<endl;
	for (i=0;i<n;i++)
	{
		for(j=0;j<3;j++)
		{
			cin>>sol[i][j];
			sol[i][j]=(lb[j]+(ub[j]-lb[j]))*(sol[i][j]);

			arr[j]=sol[i][j];
			fitness[i]=fun(arr);
		}
	}


	//finding best and minimum value

	double min=fitness[0];
	int k=0;
	for(i=1;i<n;i++)
	{
		if(fitness[i]<min)
		{
			min=fitness[i];
			k=i;
		}
	}

	cout<<"fitness min index"<<k<<endl;
	double best[3];
	for(j=0;j<3;j++)
	{
		best[j]=sol[k][j];
		cout<<best[j]<<" ";
	}
	cout<<endl;

	for (  i = 0; i <n; i ++ )
	{
		for ( j = 0; j <d; j ++ )
		{
			s[i][j] = sol[i][j];
		}
	}


	for(t=1;t<=N_iter;t++)
	{
		cout<<"for iter"<<t<<endl;
		for(i=0;i<n;i++)
		{
			if (rand()<p)
			{
				double* L=Levy(d);
				for(j=0;j<d;j++)
				{

		               	double dS=(L[j])*(sol[i][j]-best[j]);
				   sol[i][j]=sol[i][j]+dS;

				}
			}
			else
			{
				int epsilon=rand();

				int  jk[n];
				for(int z=0;z<n;z++)
					jk[z]=z;
				for(int z=0;z<n;z++)
				{
					int a,b;
					a=rand()%(n-z)+z;
					b=jk[a];
					jk[a]=jk[z];
					jk[z]=b;
				}

				for(j=0;j<d;j++)
				{

					s[i][j]=s[i][j]+epsilon*(sol[jk[1]][j]-sol[jk[2]][j]);
				}
			}
			simplebounds(s[i], lb, ub,d);
			//Evaluating  new solutions
			double fnew;

			for(j=0;j<d;j++)
			{
				arr[j]=s[i][j];
			}
			fnew=fun(arr);
			if(fnew<=fitness[i])
			{
				for (j=0;j<d;j++)
					sol[i][j]=s[i][j];
				fitness[i]=fnew;
			}
			if(fnew<min)
			{
				for (j=0;j<d;j++)
					best[j]=s[i][j];
				min=fnew;
			}

			for(j=0;j<d;j++)
			{
				cout<<sol[i][j]<<" ";

			}
			cout<<endl;
		}




		//for printing after every 100 iterations
		/*if ((t/100)==(int)t/100)
		{
			for(i=0;i<d;i++)
				cout<<best[i]<<" ";

			cout<<min;
		}*/

		//cout<<endl;
	}



	cout<<"Total number of evaluations: "<<N_iter*n<<endl;
	cout<<" fmin="<<min<<endl;
	cout<<"best values"<<endl;
	for(i=0;i<d;i++)
		cout<<" "<<best[i]<<" ";
	cout<<endl;


}

