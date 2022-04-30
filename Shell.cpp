#include <iostream>
#include<string>
#include<string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <cstring>
using namespace std;
bool searchPipe(char*comand)
{
   for(int i=0;i<strlen(comand);i++)
   {
      if(comand[i]=='|')
         return true;
   }
   return false;
}
void parsePipe (char*comand,char**arr,int &count) //takes command name then see for |
{
   char*parsed=strtok(comand,"|");
   for(int i=0;parsed!=NULL;i++)
   {
        arr[i]=strdup(parsed);
       parsed=strtok(NULL,"|");
       count++;
   }
}
void parsePipeCommand(char**arr,int size,char***temp)//converts 2d pointer to 3d pointer
{
   int i;
   for(i=0;i<size;i++)
   {
      char*parse=strtok(arr[i]," ");
      for(int j=0;parse!=NULL;j++)
      {
         temp[i][j]=strdup(parse);
         parse=strtok(NULL," ");
      }
   }
}
 
void executePipe(char***path,int n)//run the pipe
{
   int **pipes=new int*[n];
   for(int l=0;l<n;l++)
   {
        pipes[l]=new int [2];
        pipe(pipes[l]);
   }
   for(int i=0;i<n;i++)
   {
      pid_t h=fork();
      if(h==0)
      {
         if(i==0) //if first command redirect output only
         {
            dup2(pipes[i][1],STDOUT_FILENO);
         }
         else if (i==n-1)//if last command redirect input from last command only
         {
             dup2(pipes[i-1][0],STDIN_FILENO);
         }
         else //if a middle command redirect input from previous and output from new
         {
             dup2(pipes[i-1][0],STDIN_FILENO);
             dup2(pipes[i][1],STDOUT_FILENO);
         }
         
         
          for(int okk=0;path[i][okk]!=NULL;okk++){
           char* files;
           int index=0;
       for(int yay=0;path[i][okk][yay]!='\0';yay++){
 
        if(path[i][okk][yay]=='<'){
   
        files =new char [20];
          if(path[i][okk][yay+1]!='\0'){
            path[i][okk][yay]='\0';
           yay++;
           while(path[i][okk][yay]!='\0'){
           files[index]=path[i][okk][yay];
           path[i][okk][yay]='\0';
           index++;
           yay++;
       
           }
   
           }
           else{
           files=path[i][okk+1];
           delete path[i][okk];
           path[i][okk]=NULL;
           }
           
           
           int op_file=open(files,O_RDWR,0777);
           if(op_file <0){
           cout<<" INVALID FILE haiii baajiiii in < :"<<endl;
           }
         
           dup2(op_file,0);
           break;
           
           
           
         
           
           
             
           }
           else  if(path[i][okk][yay]=='>'){
   
        files =new char [20];
          if(path[i][okk][yay+1]!='\0'){
            path[i][okk][yay]='\0';
           yay++;
           while(path[i][okk][yay]!='\0'){
           files[index]=path[i][okk][yay];
           path[i][okk][yay]='\0';
           index++;
           yay++;
       
           }
   
           }
           else{
           files=path[i][okk+1];
           delete path[i][okk];
           path[i][okk]=NULL;
           }
           
           
           int op_file1=open(files,O_CREAT | O_RDWR,0777);
           perror("hogayaa hun maiiii");
           if(op_file1 <0)
           {
           cout<<" INVALID FILE haiii baajiiii in > :"<<endl;
           }
           
         //  dup2(op_file1,1);
           
              dup2(op_file1,STDOUT_FILENO);
             perror("FTIMA cutie");
             break;
           }
           }
         
         }
         
         if(execvp(path[i][0],path[i])==-1)
         {
             cout<<"Invalid Command\n";
             exit(0);
         }
      }
      else
      {
        wait(NULL);
        
        //now closing all the used pipes
          if(i==0)
          {
              close(pipes[i][1]);
          }
          else if(i==n-1)
          {
              close(pipes[i-1][0]);
          }
          else
          {
              close(pipes[i-1][0]);
              close(pipes[i][1]);
          }
      }
   }  
     
}
int main()
{


 char** argv;
  int index=0,t=0;

int i=0 , ind_count=0;



   
  string ok;
  while(ok!="exit"&&ok!="EXIT"){
    getline(cin,ok);
    if( ok=="exit")
    return 0; 
    //argv=new char*[2];
    int size=ok.length();
    //cout<<ok;
   // cout <<size;
    i=0 , ind_count=0;
    index=0,t=0;
if(ok=="exit")
return 0;
while(ok[i]!='\0')
{
if(ok[i]==' ')
{
   while(ok[i]==' ')
   {
       i++;
   }
 
ind_count++;
}
i++;
}

//cout<<ind_count<<endl;
    argv=  new char*[ind_count+3];
    int mrjao=0;
 while(ok[mrjao]!=' '&& ok[mrjao]!='\0')
  {
mrjao++;
}
   argv[index] = new char[mrjao];
   
    for ( i=0 ; i<size;i++)
{

mrjao=0;
while(ok[mrjao]!=' '&& ok[mrjao]!='\0')
{
mrjao++;

}
if(ok[i]==' '||ok[i]=='\0')
{
argv[index][t++]='\0';
//i++;
t=0;
while(ok[i]==' ')
   {
       i++;
   }
   i--;
index++;
i++;
argv[index] = new char[mrjao];
}



argv[index][t++]=ok[i];

//argv[index][k]='\0';



}
int n = ok.length();
 
    // declaring character array
    char* fullname;
   // string str_obj("GeeksForGeeks");
    fullname = &ok[0];
    //cout << char_arr;


argv[index+1]=NULL;
for(int i=0;i<ind_count+1;i++)
{

//if(
//if(argv[i]=='|')
//cout<<argv[i]<<"  "<<strlen(argv[i])<<endl;// to check k data sahi store horha
                   //h hr index py ya niiii

}






  //  cout<<endl;
   
   
    ///////////////////////////////////////////////////////////////////////////////////
    /*
   


    */
   
    ///////////////////////////////////////////////////////////////////////////////////
   
       if(searchPipe(fullname)) // fullname char array h ok ki
        {
           
            pid_t proc=fork();
            if(proc==0)
            {
                int countPipes=0;
                char*all_pipes[20];
                char**s[20];
                for(int i=0;i<20;i++)
                    s[i]=new char*[20];
                parsePipe(fullname,all_pipes,countPipes);//parse the pipe
                parsePipeCommand(all_pipes,countPipes,s);//further parse in arrays
                executePipe(s,countPipes);//execute the pipe
                return 0;
            }
            else
            {
                wait(NULL);
            }
       
        }
               
else{

  if(ok=="exit")
  return 0;
    int id=fork();
  if (id==0)
  {
 
  for(int okk=0;argv[okk]!=NULL;okk++){
           char* files;
           int index=0;
       for(int yay=0;argv[okk][yay]!='\0';yay++){
 
        if(argv[okk][yay]=='<'){
   
        files =new char [20];
          if(argv[okk][yay+1]!='\0'){
            argv[okk][yay]='\0';
           yay++;
           while(argv[okk][yay]!='\0'){
           files[index]=argv[okk][yay];
           argv[okk][yay]='\0';
           index++;
           yay++;
       
           }
   
           }
           else{
           files=argv[okk+1];
           delete argv[okk];
           argv[okk]=NULL;
           }
           
           
           int op_file=open(files,O_RDWR,0777);
           if(op_file <0){
           cout<<" INVALID FILE haiii baajiiii in < :"<<endl;
           }
         
           dup2(op_file,0);
           break;
           
           
           
         
           
           
             
           }
           else   if(argv[okk][yay]=='>'){
   
        files =new char [20];
          if(argv[okk][yay+1]!='\0'){
            argv[okk][yay]='\0';
           yay++;
           while(argv[okk][yay]!='\0'){
           files[index]=argv[okk][yay];
           argv[okk][yay]='\0';
           index++;
           yay++;
       
           }
   
           }
           else{
           files=argv[okk+1];
           delete argv[okk];
           argv[okk]=NULL;
           }
           
           
            int op_file1=open(files,O_CREAT | O_RDWR,0777);
           if(op_file1 <0){
           cout<<" INVALID FILE haiii baajiiii in > :"<<endl;
           }
         
           dup2(op_file1,1);
           break;
           
           
           
         
           
           
             
           }
           }
         
         }
         
         if(ok=="exit")
         return 0;
         
    if(execvp(argv[0],argv)==-1){
    cout<<"INVALID COMMAND"<<endl;
    return 0;
    }
   
    //if (status==-1)cout<<"CHILD TERMINATED"<<endl;
  }

  else if (id>0)
  {
  if(ok=="exit")
         return 0;
    wait(NULL);
  }

  else
  {
    cout<<"Fork failed"<<endl;
  }

 
  }
}
return 0;
}