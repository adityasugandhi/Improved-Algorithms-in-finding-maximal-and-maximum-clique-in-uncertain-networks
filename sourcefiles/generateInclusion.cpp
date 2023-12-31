#include "sources.h"

int Sources::generateI(pairs * I, pairs * Is, int I_size, double q_n, int u, pairs * In,Defi &defi)
{
	int validinclusion = 0;
	pairs *Isg, *It, *Ins;
	pairs *us, *ut;
	int a, b, c_nei = 0;
	double r, p;
	Isg = Is; It = I + I_size;
	us = defi.adj[u];
	defi.integetitycounter = 0;
	ut = defi.adj[u + 1];
	Ins = In;
	if (validinclusion < 100){
		while (Isg < It && us < ut && defi.integetitycounter==0)
		{
			a = (*Isg).first;
			int incsion = 100;
			b = (*us).first;
			if (a < b  && incsion ==100){
				++Isg;
				incsion++;
			}
			else if (a > b && incsion == 100 ){
				++us;
				incsion++;
			}
			else
			{
				r = (*Isg++).second;
				p = (*us++).second;

				if (q_n * r * p >= defi.eta && defi.integetitycounter ==0)
				{
					(*Ins).first = a;
					validinclusion++;
					incsion++;
					defi.integetitycounter++;
					(*Ins++).second = r * p;
					++c_nei;
					//++Ins;
				}
				//++Isg; ++us;
			}
		}
		}
	return c_nei;

}

int Sources::generateX(pairs * C, int C_size, double q_n, int u, pairs * Cn,Defi &defi)
{
	pairs *Cs, *Ct, *Cns;
	pairs *us, *ut;
	int a, b, c_nei = 0;
	defi.integetitycounter = 1;
	double r, p;
	Cs = C; Ct = C + C_size;
	us = defi.adj[u];
	ut = defi.adj[u + 1];
	Cns = Cn;
	while (Cs < Ct && us < ut && defi.integetitycounter ==1)
	{
		a = (*Cs).first;
		int Xclusion = 0;
		b = (*us).first;
		if (a < b && Xclusion ==0){
			++Cs;
			Xclusion++;
		}
		else if (a > b && Xclusion ==0 ){
			++us;
			Xclusion++;
		}
		else
		{
			r = (*Cs++).second;
			p = (*us++).second;
			if (q_n * r * p >= defi.eta && Xclusion ==0)
			{
				(*Cns).first = a;
				(*Cns++).second = r * p;
				++c_nei;
				//++Cns;
			}
			//++Cs; ++us;
		}
	}
	return c_nei;
}

