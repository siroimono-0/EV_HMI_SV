#include <bits/stdc++.h>
#include <limits.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main()
{
    bool flag_rere = true;
    while (flag_rere)
    {
        pid_t pid = fork();
        if (pid > 0)
        {
            // 부모
            int stat = 0;
            pid_t pid_end = waitpid(pid, &stat, 0);

            if (WIFEXITED(stat))
            {
                // 직접 비트 쉬프트 하면안댐 매크로써야댐
                int exit_code = WEXITSTATUS(stat);

                // 재시작 종료코드 85임
                // 정상 종료시 상위 2바이트 값 확인 하면댐
                if (exit_code == 85)
                {
                    // exec~~
                    cout << exit_code << " restart" << endl;
                    sleep(2);
                }
                else
                {
                    // 일반 종료시에는 런쳐 재시작해서 app돌아가게 해야함
                    // 런쳐 loop빠져나오고 종료댐
                    flag_rere = false;
                    cout << "end" << endl;
                }
            }
            else
            {
                flag_rere = false;
                cout << "sig end" << endl;
            }
        }
        else if (pid == 0)
        {
            // 자식
            char cur_path[256];

            getcwd(cur_path, sizeof(cur_path));

            string path = cur_path;
            for (int i = 0; i < 8; i++)
            {
                path.pop_back();
            }
            path += "HMI/build/Desktop_Qt_6_9_3-Debug/appHMI";
            cout << path << endl;

            char *argv[] = {(char *)path.c_str(), NULL};
            int ret = execvp(path.c_str(), argv);
            if (ret == -1)
            {
                cout << "execvp Err" << endl;
            }
        }
        else
        {
            // err
        }
    }
    return 0;
}