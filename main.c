#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Global variables. */
double TRANSCOEFF = 0.00001;
double RECOVCOEFF = 0.05;
double s_0 = 45400;
double i_0 = 2100;
double r_0 = 2500;


/* System of ODEs to solve.*/
double S(double t, double i, double s) { return -TRANSCOEFF * s * i; }
double I(double t, double s, double i) { return (TRANSCOEFF * s * i) - (RECOVCOEFF * i); }
double R(double i) { return RECOVCOEFF * i; }


void programPage();
void advancedPage();
void infoPage();

/* Main page of the program allows user to navigate using input from keyboard. */
int main() {
  
  char input = 0;

  invalid:
    printf("###############################################################\n");
    printf("#                 WELCOME TO PANDEMICS TRACKER                #\n");
    printf("#      A program which given a pandemic's current impact      #\n");
    printf("#             in your area can predic the future.             #\n");
    printf("###############################################################\n\n");

    printf("Transmission Coefficient: %lf\n", TRANSCOEFF);
    printf("Recovery Coefficient: %lf\n\n", RECOVCOEFF);

    printf("Type:\n");

    printf("       \"R\" - TO RUN\n");
    printf("       \"A\" - ADVANCED SETTINGS\n");
    printf("       \"I\" - MORE INFORMATION\n\n");
    printf("               ENTER to comfirm.\n");

  
      scanf(" %c", &input);
      switch (toupper(input)) {
        case 'R':
          system("cls");
          programPage();
          break;
        case 'A':
          system("cls");
          advancedPage();
          break;
        case 'I':
          system("cls");
          infoPage();
          break;
        default:
          system("cls");
          goto invalid;

    }
      return 0;
}


double euler(int w, double day);
void saveFile(double days, double s, double i, double r);

/* Program page of the program here is where the user can input data and recieve results. */
void programPage() {

  double days;
  double s;
  double i;
  double r;
  char input = 0;


rerun:
  printf("Enter Current Number of [Susceptible] People in your Area of Study: ");
  scanf(" %lf", &s_0);

  printf("Enter Current Number of [Infected] People in your Area of Study: ");
  scanf(" %lf", &i_0);

  printf("Enter Current Number of [Recovered + Dead] People in your Area of Study: ");
  scanf(" %lf", &r_0);

  printf("Enter the Number of Days from Today you Want to Predict. e.g. Enter [1] for tomorrow: ");
  scanf(" %lf", &days);
  system("cls");

  s = euler(1, days);
  i = euler(2, days);
  r = euler(3, days);

  printf("RESULTS (%.1lf days from today): \n", days);
  printf("There will be %.1lf susceptible people. \n", s);
  printf("There will be %.1lf infected people. \n", i);
  printf("There will be %.1lf recovered/dead people. \n\n", r);

  printf("Type:\n");

  printf("       \"ANYTHING\" - TO RE-RUN.\n");
  printf("       \"S\" - TO SAVE IN FILE\n");
  printf("       \"M\" - TO MAIN MENU\n\n");
  printf("               ENTER to comfirm.\n");

  scanf(" %c", &input);
  switch (toupper(input)) {
  case 'M':
    system("cls");
    main();
    break;
  case 'S':
    system("cls");
    saveFile(days, s, i, r);
    break;
  default:
    system("cls");
    goto rerun;

  }
}

/* Euler's Methode used to solved the system of ODEs above. */
double euler(int w, double days) {
  
  int N = 100; // number or steps.
  double t_0 = 0;
  double t_f = days;
  double h = (t_f - t_0) / ((double)N); //step size.
  double t = t_0, sEu = s_0, iEu = i_0, tmpsEu = s_0, tmpiEu = i_0;
  double P = s_0 + i_0 + r_0;

  for (int n = 1; n <= N; n++) { // iteration to solve ODEs numerically.

    tmpsEu = sEu + h * S(t, sEu, iEu);
    tmpiEu = iEu + h * I(t, sEu, iEu);

    sEu = tmpsEu;
    iEu = tmpiEu;

    t += h;
  }
  double rEu = P - sEu - iEu;

  if (w == 1) {
    return sEu;
  }
  else if (w == 2) {
    return iEu;
  }
  else {
    return rEu;
  }
}

/*Advanced page of the program here the user can modify the constants to predict different epidemics. */
void advancedPage() {

  char input = 0;

  printf("THIS PROGRAM IS RE-CONFIGURABLE TO PREDICT THE SPREAD OF OTHER DISEASES (INPUT THE FOLLOWING): \n");
  printf("WARRNING ONLY CONFIGURE IF YOU KNOW WHAT YOU ARE DOING!\n\n");

  printf("Enter Transmission Coefficient of Your Disease (DEFAULT = 0.00001): ");
  scanf("%lf", &TRANSCOEFF);

  printf("Enter Recovery Coefficient of Your Disease (DEFAULT = 0.05): ");
  scanf("%lf", &RECOVCOEFF);

  printf("\nType:\n");

  printf("       \"ANYTHING\" - TO MAIN MENU WITH THIS CONFIGURATION\n\n");
  printf("               ENTER to comfirm.\n");

  scanf(" %c", &input);
  switch (toupper(input)) {
  default:
    system("cls");
    main();

  }
}

/* Information page of the program here the user can learn more about how the SIR model works, also recognitions are given. */
void infoPage() {

  char input = 0;

  printf("ABOUT: \n\n");

  printf("This program approximates the solution to the SIR model using Euler's Method. \n\n");
  printf("The SIR model is a simple mathematical model of epidemics. An epidemic is\n");
  printf("when the number of people infected with a disease is increasing in a population.\n");
  printf("S, I, and R stand for:\n");
  printf("  S - susceptible. These are people that are not infected with the disease yet. However, they\n");
  printf("    are not immune to it either and so they can become infected with the disease in the future.\n");
  printf("  I - infected or infectious.These are people that are infected with the disease\n");
  printf("    and can transmit the disease to susceptible people.\n");
  printf("  R - recovered. These are people who have recovered from the disease and are immune,\n");
  printf("    so they can no longer be infected with the disease.\n");
  printf("For more go to https://simple.wikipedia.org/wiki/SIR_model \n\n");

  printf("Huge Thanks To:\n");
  printf("  Shelly Duarte (my gf).\n");
  printf("  Dr. William D. Gillam (my diff. eq. professor).\n");
  printf("  Lorenzo Sadun (https://www.youtube.com/channel/UC3IZYipZ6A_Rs5v0GdwUM7Q).\n");
  printf("  Sanjay C. Gawande, Pradip P.Kolhe & Dr.Prakash R.Kolhe (https://www.ijettcs.org/Volume6Issue3/IJETTCS-2017-05-08-13.pdf).\n");
  printf("  The Organic Chemestry Tutor (https://www.youtube.com/channel/UCEWpbFLzoYGPfuWUMFPSaoA).\n\n");

  printf("Created by: David Langus & Jacob Arteaga. <3\n\n");

  printf("Type:\n");

  printf("       \"ANYTHING\" - TO MAIN MENU \n\n");
  printf("               ENTER to comfirm.\n");

  scanf(" %c", &input);
  switch (toupper(input)) {
  default:
    system("cls");
    main();

  }
}

void saveFile(double days, double s, double i, double r) {
  
  char input = 0;

  // creating file pointer to work with files
  FILE* fptr;

  // opening file in writing mode
  fptr = fopen("results.txt", "w");

  // exiting program 
  if (fptr == NULL) {
    printf("Error!");
    exit(1);
  }
  
  fprintf(fptr, "RESULTS (%.1lf days from today): \nThere will be %.1lf susceptible people.\nThere will be %.1lf infected people.\nThere will be %.1lf recovered/dead people. ", days, s, i, r);
  fclose(fptr);
  printf("Saved Successfully!\n\n");

  printf("Type:\n");

  printf("       \"ANYTHING\" - TO MAIN MENU \n\n");
  printf("               ENTER to comfirm.\n");

  scanf(" %c", &input);
  switch (toupper(input)) {
  default:
    system("cls");
    main();

  }
  printf("Error!");
}

