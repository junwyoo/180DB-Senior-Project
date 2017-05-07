#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include "neural_network.h"


#define BUFF_SIZE 1024
int checkForNetFile(char *name)
{
  char *filenname = (char*)malloc(sizeof(char)*BUFF_SIZE);
  FILE *t_fp, *w_fp, *r_fp, *j_fp, *sa_fp, *sd_fp; //fps for .net files
  
  sprintf(filename,"%s/TRAINING_%s.net",name,name);
  t_fp = fopen(filename, "r");

  if(t_fp == NULL) // if cannot open the file
    {
      printf("Error: .net file not found\n");
      //prompt for training
      printf("Do you wish to train data for: %s? [y/n]\n",name);
      type = getchar();
      if(type == '\n') type = getchar();
      while(type != 'n' && type != 'y')
	{
	  printf("Wrong input. [y/n] \n");
	  type = getchar();
	  if(type == '\n') type = getchar();
	}
      printf("You answered: %c\n",type);
      if(type == 'n')
	{
	  printf("Okay.. BYE!\n");
	  exit(1);
	}
      else
	{
	  sprintf(command,"mkdir %s",name);
	  system(command);
	  printf("Directory named: %s is made\n",name);
	  //DO the training
	  printf("Training!\n");
	}
    }
  else
    {
      printf("The files exist.\n");
    }
}
int main(int argc, char** argv)
{
  int c;
  char type; // input char
  char *filename = (char*)malloc(sizeof(char)*BUFF_SIZE);//for fopen
  char *command = (char*)malloc(sizeof(char)*BUFF_SIZE);//for shell cmd
  char* name = (char*)malloc(sizeof(char) * BUFF_SIZE);//user name
  int test_flag = 0; //set to 1 if "test" option
  FILE *t_fp, *w_fp, *r_fp, *j_fp, *sa_fp, *sd_fp; //fps for .net files
  
  if (argc == 1)
  {
    fprintf(stderr,"Error: Need Arguments.\nex)./main yoo\n");
    exit(1);
  }
  
  /* [INPUT EXAMPLE]
     ./main --train walking_3.csv   => train with name "yoo" & test
     ./main --test yoo    => test with name "yoo"

     ./main yoo => check for .net file for "yoo", if not prompt to user, 
     train, and test */

  /* Option Handling Starts */
  while(1) 
    {
      static struct option long_options[]=
	{
	  {"train",required_argument,0,'n'},
	  {"test",required_argument,0,'t'},
	  {0,0,0,0}
	};
      c = getopt_long(argc, argv, "", long_options, 0);

      if(c == -1)
	break;
      switch(c)
	{
	case'n':
	  test_flag = 0;
	  break;
	case't':
	  test_flag = 1;
	  break;
	case':':
	case'?':
	default:
	  fprintf(stderr,"ex) \"--train yoo\" or \"--test yoo\"\n");
	  exit(1);
	}
      if(optarg[0] == '-' && optarg[1] == '-')
	{
	  fprintf(stderr,"Error: Requires an Argument\n");
	  exit(1);
	}
      else if(argv[optind] != '\0' && argv[optind][0] != '-' && argv[optind][1]
	      != '-')
	{
	  fprintf(stderr, "Error: More than One Argument\n");
	  exit(1);
	}
      name = optarg;

    }
  /*Option handling ends*/

  if(argc == 2)
    {
      name = argv[1];
      printf("Checking for .net file under the name: %s...\n",name);
      //checking for .net files
      sprintf(filename,"%s/TRAINING_%s.net",name,name);
      t_fp = fopen(filename, "r");

      if(t_fp == NULL) // if cannot open the file
	{
	  printf("Error: .net file not found\n");
	  //prompt for training
	  printf("Do you wish to train data for: %s? [y/n]\n",name);
	  type = getchar();
	  if(type == '\n') type = getchar();
	  while(type != 'n' && type != 'y')
	    {
	      printf("Wrong input. [y/n] \n");
	      type = getchar();
	      if(type == '\n') type = getchar();
	    }
	  printf("You answered: %c\n",type);
	  if(type == 'n')
	    {
	      printf("Okay.. BYE!\n");
	      exit(1);
	    }
	  else
	    {
	      sprintf(command,"mkdir %s",name);
	      system(command);
	      printf("Directory named: %s is made\n",name);
	      //DO the training
	      printf("Training!\n");
	    }
	}
      else
	{
	  printf("The files exist.\n");
	}

      printf("Testing!\n");
      //Now DO the testing

      exit(0);
    }
  if(!test_flag)
    {
      fprintf(stdout,"Your name is: %s\n",name);
      /* train data */

      printf("Training!\n");
      
      //train_network(training_file, WALKING_name);
      //train_network(training_file, RUNNING_name);
      //train_network(training_file, JUMPING_name);
      //train_network(training_file, STAIR_ASCENT_name);
      //train_network(training_file, STAIR_DESCENT_name);

      printf("Testing!\n");
      //test_neural_network(class_v,num_rows,name);
      
    }
  else
    {
      fprintf(stdout,"Your name is: %s\n",name);
      /* test data */

      //check if .net file exists, if not prompt
      printf("Error: .net file not found under the name: %s\n",name);
      //test_neural_network(class_v,num_rows,name);
      printf("Testing!\n");
    }
  /*
  FILE* fp;
  fp = fopen("yoo/WALKING_yoo.net", "r");
  if(fp==NULL)
    printf("open failed\n");
  else
    printf("open succeed\n");
  */
  exit(0);

mkdir("test_dir",0777);
}
