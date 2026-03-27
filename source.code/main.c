#include<stdio.h>
#include<unistd.h>
void convert(int total_sec, int *hours, int *minutes, int *seconds){
     *hours = total_sec/3600;
     *minutes = (total_sec%3600)/ 60;
     *seconds = total_sec % 60;
}

void read_cpu(long *tot,long *idle){
    FILE *rp = fopen("/proc/stat","r");
    long user,nice,sys ,idle_t,iowait,irq,softirq,steal;
    fscanf(rp,"cpu %ld %ld %ld %ld %ld %ld %ld %ld",&user,&nice,&sys,&idle_t,&iowait,&irq,&softirq,&steal);
    fclose(rp);
    *idle = idle_t + iowait;
    *tot = user + nice + sys + idle_t + iowait + irq + softirq + steal;
}

double usage(){
    long tot1,idle1;
    long tot2,idle2;
    read_cpu(&tot1,&idle1);
    sleep(1);
    read_cpu(&tot2,&idle2);
    long tot_diff=tot2-tot1;
    long idle_diff=idle2-idle1;
return (double)(tot_diff - idle_diff)/tot_diff *100.0;
}
int main(){
    double uptime;
    int total_sec;
    int h,m,s;
    long mem_total = 0;
    long mem_ava = 0;
    
 FILE *fp = fopen("/proc/uptime","r");
 if (fp == NULL){
     perror("Error opening file\n");
     return 1;
    }
 fscanf(fp,"%lf",&uptime);
fclose(fp);
total_sec = (int) uptime;
convert(total_sec,&h,&m,&s);

 FILE *mp = fopen("/proc/meminfo","r");
if (mp == NULL){
     perror("Error opening file\n");
     return 1;
    }
char line[256];
while(fgets(line, sizeof(line),mp)){
if (sscanf(line,"MemTotal: %ld kB",&mem_total)==1)
    continue;
if (sscanf(line,"MemAvailable: %ld kB",&mem_ava)==1)
    continue;}
fclose(mp);
double totalgb= mem_total / (1024.0 * 1024.0);
double avalgb= mem_ava /(1024.0 * 1024.0);
double  mem_used = totalgb - avalgb;
double percentage = ( mem_used / totalgb) * 100;
double cpu = usage();

printf("Uptime: %dh %dm %ds\n",h,m,s);
printf("Memory: %.2fGiB / %.2fGiB (%.2f%%)\n",mem_used,totalgb,percentage);  
printf("CPU Usage: %.2f%%\n",cpu);
return 0; 
}
