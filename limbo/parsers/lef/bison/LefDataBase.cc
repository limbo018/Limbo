/*************************************************************************
    > File Name: LefDataBase.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Thu 11 Dec 2014 04:28:14 PM CST
 ************************************************************************/

#include "LefDataBase.h"

namespace LefParser {

LefDataBase::LefDataBase()
{
	current_version = 5.6;
}
double LefDataBase::current_version() const 
{return m_current_version;}
void LefDataBase::current_version(double cv)
{m_current_version = cv;}

} // namespace LefParser

namespace LefParser {

void lefError(int msgNum, const char *s) {
   char* str;
   int len = strlen(token)-1;
   int pvLen = strlen(pv_token)-1;

   /* PCR 690679, probably missing space before a ';' */
   if (strcmp(s, "parse error") == 0) {
      if ((len > 1) && (token[len] == ';')) {
         str = (char*)lefMalloc(strlen(token)+strlen(s)+strlen(lefrFileName)
                                +350);
         sprintf(str, "ERROR (LEFPARS-%d): %s, see file %s at line %d\nLast token was <%s>, space is missing before <;>\n",
              msgNum, s, lefrFileName, lef_nlines, token);
      } else if ((pvLen > 1) && (pv_token[pvLen] == ';')) {
         str = (char*)lefMalloc(strlen(pv_token)+strlen(s)+strlen(lefrFileName)
                                +350);
         sprintf(str, "ERROR (LEFPARS-%d): %s, see file %s at line %d\nLast token was <%s>, space is missing before <;>\n",
              msgNum, s, lefrFileName, lef_nlines-1, pv_token);
      } else if ((token[0] == '"') && (spaceMissing)) {
         /* most likely space is missing after the end " */
         str = (char*)lefMalloc(strlen(pv_token)+strlen(s)+strlen(lefrFileName)
                                +350);
         sprintf(str, "ERROR (LEFPARS-%d): %s, see file %s at line %d\nLast token was <%s\">, space is missing between the closing \" of the string and ;.\n",
              1010, s, lefrFileName, lef_nlines, token);
         spaceMissing = 0;
      } else {
         str = (char*)lefMalloc(strlen(token) + strlen(lefrFileName) + 350);
         sprintf(str, "ERROR (LEFPARS-%d): Lef parser has encountered an error in file %s at line %d, on token %s.\nProblem can be syntax error on the lef file or an invalid parameter name.\nDouble check the syntax on the lef file with the LEFDEF Reference Manual.\n",
              msgNum, lefrFileName, lef_nlines, token);
      }
   } else if (strcmp(s, "syntax error") == 0) {  /* linux machines */
      if ((len > 1) && (token[len] == ';')) {
         str = (char*)lefMalloc(strlen(token)+strlen(s)+strlen(lefrFileName)
                                +350);
         sprintf(str, "ERROR (LEFPARS-%d): %s, see file %s at line %d\nLast token was <%s>, space is missing before <;>\n",
              msgNum, s, lefrFileName, lef_nlines, token);
      } else if ((pvLen > 1) && (pv_token[pvLen] == ';')) {
         str = (char*)lefMalloc(strlen(pv_token)+strlen(s)+strlen(lefrFileName)
                                +350);
         sprintf(str, "ERROR (LEFPARS-%d): %s, see file %s at line %d\nLast token was <%s>, space is missing before <;>\n",
              msgNum, s, lefrFileName, lef_nlines-1, pv_token);
      } else if ((token[0] == '"') && (spaceMissing)) {
         /* most likely space is missing after the end " */
         str = (char*)lefMalloc(strlen(pv_token)+strlen(s)+strlen(lefrFileName)
                                +350);
         sprintf(str, "ERROR (LEFPARS-%d): %s, see file %s at line %d\nLast token was <%s\">, space is missing between the closing \" of the string and ;.\n",
              1011, s, lefrFileName, lef_nlines, token);
         spaceMissing = 0;
      } else {
         str = (char*)lefMalloc(strlen(token) + strlen(lefrFileName) + 350);
         sprintf(str, "ERROR (LEFPARS-%d): Lef parser has encountered an error in file %s at line %d, on token %s.\nProblem can be syntax error on the lef file or an invalid parameter name.\nDouble check the syntax on the lef file with the LEFDEF Reference Manual.\n",
              msgNum, lefrFileName, lef_nlines, token);
      }
   } else {
      str = (char*)lefMalloc(strlen(token) + strlen(s) +
                             strlen(lefrFileName) + 350);
      sprintf(str, "ERROR (LEFPARS-%d): %s Error in file %s at line %d, on token %s.\n",
           msgNum, s, lefrFileName, lef_nlines, token);
   }
   fflush(stdout);
   lefiError(str);
   free(str);
   lef_errors++;
}
/* All warning starts with 2000 */
/* All warning within lefWarning starts with 2500 */
void lefWarning(int msgNum, const char *s) {
   int i;

   for (i = 0; i < nDMsgs; i++) {  /* check if warning has been disable */
      if (disableMsgs[i] == msgNum)
         return;  /* don't print out any warning since msg has been disabled */
   }

   if (lefiWarningLogFunction) {
      char* str = (char*)lefMalloc(strlen(token)+strlen(s)+strlen(lefrFileName)
                                   +350);
      sprintf(str, "WARNING (LEFPARS-%d): %s See file %s at line %d.\n",
              msgNum, s, lefrFileName, lef_nlines);
      (*lefiWarningLogFunction)(str);
      free(str);
   } else if (lefrLog) {
      fprintf(lefrLog, "WARNING (LEFPARS-%d): %s See file %s at line %d\n",
              msgNum, s, lefrFileName, lef_nlines);
   } else {
      if (!hasOpenedLogFile) {
         if ((lefrLog = fopen("lefRWarning.log", "w")) == 0) {
            printf("WARNING (LEFPARS-2500): Unable to open the file lefRWarning.log in %s.\n",
            getcwd(NULL, 64));
            printf("Warning messages will not be printed.\n");
         } else {
            hasOpenedLogFile = 1; 
            fprintf(lefrLog, "Warnings from file: %s\n\n", lefrFileName);
            fprintf(lefrLog, "WARNING (LEFPARS-%d): %s See file %s at line %d\n",
                    msgNum, s, lefrFileName, lef_nlines);
         }
      } else {
         if ((lefrLog = fopen("lefRWarning.log", "a")) == 0) {
            printf("WARNING (LEFPARS-2501): Unable to open the file lefRWarning.log in %s.\n",
            getcwd(NULL, 64));
            printf("Warning messages will not be printed.\n");
         } else {
            fprintf(lefrLog, "\nWarnings from file: %s\n\n", lefrFileName);
            fprintf(lefrLog, "WARNING (LEFPARS-%d): %s See file %s at line %d\n",
                    msgNum, s, lefrFileName, lef_nlines);
         }
      }
   }
   lef_warnings++;
}
/* All info starts with 3000 */
/* All info within lefInfo starts with 3500 */
void lefInfo(int msgNum, const char *s) {
   int i;

   for (i = 0; i < nDMsgs; i++) {  /* check if info has been disable */
      if (disableMsgs[i] == msgNum)
         return;  /* don't print out any info since msg has been disabled */
   }

   if (lefiWarningLogFunction) {
      char* str = (char*)lefMalloc(strlen(token)+strlen(s)+strlen(lefrFileName)
                                   +350);
      sprintf(str, "INFO (LEFPARS-%d): %s See file %s at line %d.\n",
              msgNum, s, lefrFileName, lef_nlines);
      (*lefiWarningLogFunction)(str);
      free(str);
   } else if (lefrLog) {
      fprintf(lefrLog, "INFO (LEFPARS-%d): %s See file %s at line %d\n",
              msgNum, s, lefrFileName, lef_nlines);
   } else {
      if (!hasOpenedLogFile) {
         if ((lefrLog = fopen("lefRWarning.log", "w")) == 0) {
            printf("WARNING (LEFPARS-3500): Unable to open the file lefRWarning.log in %s.\n",
            getcwd(NULL, 64));
            printf("Info messages will not be printed.\n");
         } else {
            hasOpenedLogFile = 1;
            fprintf(lefrLog, "Info from file: %s\n\n", lefrFileName);
            fprintf(lefrLog, "INFO (LEFPARS-%d): %s See file %s at line %d\n",
                    msgNum, s, lefrFileName, lef_nlines);
         }
      } else {
         if ((lefrLog = fopen("lefRWarning.log", "a")) == 0) {
            printf("WARNING (LEFPARS-3500): Unable to open the file lefRWarning.log in %s.\n",
            getcwd(NULL, 64));
            printf("Info messages will not be printed.\n");
         } else {
            fprintf(lefrLog, "\nInfo from file: %s\n\n", lefrFileName);
            fprintf(lefrLog, "INFO (LEFPARS-%d): %s See file %s at line %d\n",
                    msgNum, s, lefrFileName, lef_nlines);
         }
      }
   }
}
void * lefMalloc(int lef_size) {
   void * mallocVar;

   if (lefiMallocFunction)
      return (*lefiMallocFunction)(lef_size);
   else {
      mallocVar = (void*)malloc(lef_size);
      if (!mallocVar) {
         fprintf(stderr, "ERROR (LEFPARS-1009): Not enough memory, stop parsing!\n");
         exit (1);
      }
      return mallocVar;
   }
}
void * lefRealloc(void *name, int lef_size) {
   if (lefiReallocFunction)
      return (*lefiReallocFunction)(name, lef_size);
   else
      return (void*)realloc(name, lef_size);
}
void lefFree(void *name) {
   if (lefiFreeFunction)
      (*lefiFreeFunction)(name);
   else
      free(name);
}
int comp_str(const char *s1, int op, const char *s2)
{
	int k = strcmp(s1, s2);
	switch (op) {
		case C_EQ: return k == 0;
		case C_NE: return k != 0;
		case C_GT: return k >  0;
		case C_GE: return k >= 0;
		case C_LT: return k <  0;
		case C_LE: return k <= 0;
	}
	return 0;
}
int comp_num(double s1, int op, double s2)
{
	double k = s1 - s2;
	switch (op) {
		case C_EQ: return k == 0;
		case C_NE: return k != 0;
		case C_GT: return k >  0;
		case C_GE: return k >= 0;
		case C_LT: return k <  0;
		case C_LE: return k <= 0;
	}
	return 0;
}
int validNum(int values)
{
    switch (values) {
        case 100:
        case 200:
        case 1000:
        case 2000:
                return 1; 
        case 10000:
        case 20000:
             if (versionNum < 5.6) {
                if (lefrUnitsCbk) {
                  if (unitsWarnings++ < lefrUnitsWarnings) {
                    outMsg = (char*)lefMalloc(10000);
                    sprintf (outMsg,
                       "Error found when processing LEF file '%s'\nUnit %d is a version 5.6 or later syntax\nYour lef file is defined with version %g",
                    lefrFileName, values, versionNum);
                    lefError(1501, outMsg);
                    lefFree(outMsg);
                  }
                }
                return 0;
             } else
                return 1;
    }
    if (unitsWarnings++ < lefrUnitsWarnings) {
       outMsg = (char*)lefMalloc(10000);
       sprintf (outMsg,
          "The value %d defined for LEF UNITS DATABASE MICRONS is invalid\n. Correct value is 100, 200, 1000, 2000, 10000, or 20000", values);
       lefError(1502, outMsg);
       lefFree(outMsg);
    }
    CHKERR();
    return 0;
}
int zeroOrGt(double values)
{
    if (values < 0)
      return 0;
    return 1;
}

} // namespace LefParser
