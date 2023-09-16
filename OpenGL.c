/*** M2000: Portable P2000 emulator *****************************************/
/***                                                                      ***/
/***                             OpenGL.c                                 ***/
/***                                                                      ***/
/*** This file contains the OpenGL interface                              ***/
/***                                                                      ***/
/*** Copyright (C) Gert Nutterts, 2023                                    ***/
/*** License: MIT                                                         ***/
/****************************************************************************/

#include "P2000.h"
#include "Unix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

char *Title="M2000 Unix/OpenGL"; /* Title for -help output                   */

int videomode=0; 
static byte *FontBuf;
static int OldTimer; 


/****************************************************************************/
/*** This function is called by the screen refresh drivers to copy the    ***/
/*** off-screen buffer to the actual display                              ***/
/****************************************************************************/
static void PutImage (void)
{
}

/****************************************************************************/
/*** This function is called when a key is pressed or released. It        ***/
/*** updates the P2000 keyboard matrix and checks for special keypresses  ***/
/*** like F5 (toggle sound on/off)                                        ***/
/****************************************************************************/
static void keyb_handler (int code,int newstatus)
{
}

/****************************************************************************/
/*** This function looks for keyboard events and passes them to the       ***/
/*** keyboard handler                                                     ***/
/****************************************************************************/
static void keyboard_update (void)
{
}

/****************************************************************************/
/*** This function deallocates all resources taken by InitMachine()       ***/
/****************************************************************************/
void TrashMachine(void)
{
}

/****************************************************************************/
/*** Swap bytes in an integer. Called to support displays with a          ***/
/*** non-standard byte order                                              ***/
/****************************************************************************/
static unsigned SwapBytes (unsigned val,unsigned depth)
{
}

/****************************************************************************/
/*** This function allocates all resources used by the X-Windows          ***/
/*** implementation                                                       ***/
/****************************************************************************/
int InitMachine(void)
{
 return 1;
}

/****************************************************************************/
/*** This function loads a font and converts it if necessary              ***/
/****************************************************************************/
int LoadFont (char *filename)
{
 FILE *F;
 int i,j,k,l,c,d;
 char *TempBuf;
 if (Verbose) printf("Loading font %s...\n",filename);
 if (Verbose) printf ("  Allocating memory... ");
 if (!FontBuf)
 {
  FontBuf=malloc (8960);
  if (!FontBuf)
  {
   if (Verbose) puts ("FAILED");
   return 0;
  }
 }
 TempBuf=malloc (2240);
 if (!TempBuf)
 {
  if (Verbose) puts ("FAILED");
  return 0;
 }
 if (Verbose) puts ("OK");
 if (Verbose) printf ("  Opening... ");
 i=0;
 F=fopen(filename,"rb");
 if (F)
 {
  printf ("Reading... ");
  if (fread(TempBuf,2240,1,F)) i=1;
  fclose(F);
 }
 if (Verbose) puts ((i)? "OK":"FAILED");
 if (!i) return 0;

 /* Stretch characters to 12x20 */
 for (i=0;i<96*10;i+=10)
 {
  for (j=0;j<10;++j)
  {
   c=TempBuf[i+j]; k=0;
   if (c&0x10) k|=0x0300;
   if (c&0x08) k|=0x00C0;
   if (c&0x04) k|=0x0030;
   if (c&0x02) k|=0x000C;
   if (c&0x01) k|=0x0003;
   l=k;
   if (videomode && j!=9)
   {
    d=TempBuf[i+j+1];
    if ((c&0x10) && (d&0x08) && !(d&0x10)) l|=0x0080;
    if ((c&0x08) && (d&0x04) && !(d&0x08)) l|=0x0020;
    if ((c&0x04) && (d&0x02) && !(d&0x04)) l|=0x0008;
    if ((c&0x02) && (d&0x01) && !(d&0x02)) l|=0x0002;
    if ((d&0x10) && (c&0x08) && !(d&0x08)) l|=0x0100;
    if ((d&0x08) && (c&0x04) && !(d&0x04)) l|=0x0040;
    if ((d&0x04) && (c&0x02) && !(d&0x02)) l|=0x0010;
    if ((d&0x02) && (c&0x01) && !(d&0x01)) l|=0x0004;
   }
   if (videomode && j!=0)
   {
    d=TempBuf[i+j-1];
    if ((c&0x10) && (d&0x08) && !(d&0x10)) k|=0x0080;
    if ((c&0x08) && (d&0x04) && !(d&0x08)) k|=0x0020;
    if ((c&0x04) && (d&0x02) && !(d&0x04)) k|=0x0008;
    if ((c&0x02) && (d&0x01) && !(d&0x02)) k|=0x0002;
    if ((d&0x10) && (c&0x08) && !(d&0x08)) k|=0x0100;
    if ((d&0x08) && (c&0x04) && !(d&0x04)) k|=0x0040;
    if ((d&0x04) && (c&0x02) && !(d&0x02)) k|=0x0010;
    if ((d&0x02) && (c&0x01) && !(d&0x01)) k|=0x0004;
   }
   FontBuf[(i+j)*4+0]=k>>8; FontBuf[(i+j)*4+2]=l>>8;
   FontBuf[(i+j)*4+1]=k>>0; FontBuf[(i+j)*4+3]=l>>0;
  }
 }
 for (i=96*10;i<(96+128)*10;++i)
 {
  c=TempBuf[i]; k=0;
  if (c&0x20) k|=0x0C00;
  if (c&0x10) k|=0x0300;
  if (c&0x08) k|=0x00C0;
  if (c&0x04) k|=0x0030;
  if (c&0x02) k|=0x000C;
  if (c&0x01) k|=0x0003;
  FontBuf[i*4]=FontBuf[i*4+2]=k>>8; FontBuf[i*4+1]=FontBuf[i*4+3]=k;
 }
 free (TempBuf);
 return 1;
}

/****************************************************************************/
/*** This function is called every interrupt to check for window events   ***/
/*** and update the keyboard matrix                                       ***/
/****************************************************************************/
void Keyboard(void)
{
}

/****************************************************************************/
/*** This function is called every interrupt to flush the sound pipes and ***/
/*** sync the emulation                                                   ***/
/****************************************************************************/
void FlushSound (void)
{
}

/****************************************************************************/
/*** This function is called when the sound register is written to        ***/
/****************************************************************************/
void Sound (int toggle)
{
}

/****************************************************************************/
/*** Pause the specified time                                             ***/
/****************************************************************************/
void Pause (int ms)
{
 int i,j;
 j=ReadTimer();
 i=j+ms*1000;
 while ((j-i)<0) j=ReadTimer();
 OldTimer=j;
}

/****************************************************************************/
/*** Put a character in the display buffer                                ***/
/****************************************************************************/
static inline void PutChar (int x,int y,int c,int fg,int bg,int si)
{
}

/****************************************************************************/
/*** Common.h contains the system-independent part of the screen refresh  ***/
/*** drivers                                                              ***/
/****************************************************************************/
#include "Common.h"
