#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <pwd.h>

#define __USE_XOPEN  // strptime을 사용하기 위해 추가
#include <time.h>

//#define DEBUG

// 현재 시간을 buf에 저장
void get_time(char* buf){
    time_t cur_time;
    struct tm *tm_ptr;
    
    cur_time = time(NULL);
    tm_ptr = localtime(&cur_time);

    // sprintf(buf, "%d%02d%02d_%02d",tm_ptr->tm_year+1900,tm_ptr->tm_mon+1,tm_ptr->tm_mday,tm_ptr->tm_hour);
    strftime(buf, 12, "%4Y%2m%2d_%l", tm_ptr);
}

// time1, time2의 시간의 차이를 반환
// time 1이 클때 양수
// time 2가 클 때 음수 
// 같을 때는 0
double cmp_time(char* time1, char* time2){
    struct tm* tmp[2];
    time_t t_fst, t_snd;
    int i;
    double dif_time;

#ifdef DEBUG
    printf("%s\n", time1);
    printf("%s\n", time2);
#endif

    for(int i=0; i<2; i++){
        tmp[i] = malloc(sizeof(struct tm));
        tmp[i]->tm_sec =0;
        tmp[i]->tm_min = 0;
        tmp[i]->tm_isdst = 0;
    }

    // string -> struct tm으로 변환
    if(strptime(time1, "%Y%02m%02d_%0l",tmp[0])==NULL) perror("strptime error");
    if(strptime(time2, "%Y%02m%02d_%0l",tmp[1])==NULL) perror("strptime error");

#ifdef DEBUG
    printf("%4d%2d%2d_%2d\n",1900+tmp[0]->tm_year, 1+tmp[0]->tm_mon, tmp[0]->tm_mday,tmp[0]->tm_hour);
    printf("sec : %d, min : %d, tm_isdst : %d\n", tmp[0]->tm_sec, tmp[0]->tm_min, tmp[0]->tm_isdst);
    printf("%4d%2d%2d_%2d\n",1900+tmp[1]->tm_year, 1+tmp[1]->tm_mon, tmp[1]->tm_mday,tmp[1]->tm_hour);
    printf("sec : %d, min : %d, tm_isdst : %d\n", tmp[1]->tm_sec, tmp[1]->tm_min, tmp[1]->tm_isdst);
#endif

    // struct tm -> time_t로 변환
    t_fst = mktime(tmp[0]);
    t_snd = mktime(tmp[1]);

    // time_t type의 변수를 비교
    dif_time = difftime(t_fst,t_snd);

#ifdef DEBUG
    printf("%f\n", dif_time);
#endif

    free(tmp[0]);
    free(tmp[1]);

    return dif_time;
}

// /home/user_name/black 하위에 디렉토리 생성
void make_directory(char *dir_name){
    char path[50] = "/";
    int ret;
    
    struct passwd *user_pw;
    user_pw = getpwuid(getuid());

    strcat(path, user_pw->pw_dir);
    strcat(path, "/blackbox/");   


    if ( 0 != access(path, R_OK)){
        printf("blackbox 디렉토리 생성\n");
        printf("%s\n", path);

        if((ret=mkdir(path, 0755) == -1)){
            perror("mkdir");
        }

    }

    strcat(path, dir_name);
    if ( 0 != access(path, R_OK)){
        printf("시간  디렉토리 생성\n");
        printf("%s\n", path);

        if((ret=mkdir(path, 0755) == -1)){
            perror("mkdir");
        }
    } else{
        printf("directory alreay exists!\n");
    }
}

// 디바이스 연결 상태 확인
void chkDevide() {}

// 디렉토리 존재 여부 확인
void chkDirectory(char* dir_name) {}

// 디스크 용량 확인
int chkDiskUsage(char *device_name)

// 디렉토리, 하위 파일 삭제
void rmDirectory() {}

// 디렉토리 내 파일 리스트 확인
int getDiretoryLIst(char* base_path, struct  dirent **namelist;) {
	int     count;
	int     idx;

	
	if ((count = scandir(base_path, &namelist, NULL, alphasort)) == -1) {
		fprintf(stderr, "%s Directory Scan Error: %s\n", argv[1], strerror(errno));
		return 1;
	}

	for (idx = 0; idx < count; idx++) {
		printf("%s\n", namelist[idx]->d_name);
	}

	// 건별 데이터 메모리 해제
	//for (idx = 0; idx < count; idx++) {
	//	free(namelist[idx]);
	//}

	//// namelist에 대한 메모리 해제
	//free(namelist);

	return count;
}

// 현재 사용 가능 용량 확인
long GetAvailableSpace(const char* path)
{
	struct statvfs stat;

	if (statvfs(path, &stat) != 0) {
		// error happens, just quits here
		return -1;
	}

	// the available size is f_bsize * f_bavail
	return stat.f_bsize * stat.f_bavail;
}
// blackbox 녹화
void recVideo() {}

int main(int argc, char *argv[]){
	char base_path = "/home/song/";
	struct dirent **dir_list;
	cnt = getDiretoryLIst(base_path, dir_list);
	
	for (int idx = 0; idx < cnt; idx++) {
		free(namelist[idx]);
	}

	free(dir_list);

    return 0;    
}
