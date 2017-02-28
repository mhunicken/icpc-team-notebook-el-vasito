char mu[MAX] = {0,1};
void mobius(){
    for (int i=1;i<MAX;i++)
        if (mu[i])
            for (int j=2*i;j<MAX;j+=i) mu[j]-=mu[i];
}