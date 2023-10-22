/*

TOTALLY CUBULAR BY SLIPSTREAM
A NINTENDO WII DEMO FOR TRSAC 2023 - AARHUS, DENMARK
CODE, GFX + MUSIC: TÔBACH
GFX: RACCOONVIOLET
SUPPORT: TARGZ, MOLIVE & CRYPT


IDEAS:
more 90s themeing(?)
conways game of life greetz(??)


TODO:
3d model converter (prob something in python)
oh yea music too that'd be cool


GREETZ:
ATTENTION WHORE, BITSHIFTERS, RIFT, HAUJOBB, TUHB, HOOY-PROGRAM, LOGICOMA, T$ & SUNSPIRE, SVATG, SCENEPT, AND YOU !!

arr[y*width+x] = val

2d rotation shiz
x' = x*cos(theta) + y * -sin(theta)
y' = x*sin(theta) + y * cos(theta)

*/

#include <grrlib.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

#include <wiiuse/wpad.h>

#include <asndlib.h>
#include <mp3player.h>

#include "gfx/font.h"
#include "gfx/tubular.h"
#include "gfx/raccoon.h"
#include "gfx/tubulartext.h"

//miis
//atw
#include "gfx/miis/losso.h"
//bitshifters
#include "gfx/miis/kieran.h"
#include "gfx/miis/pmalin.h"
//rift
#include "gfx/miis/jtruk.h"
#include "gfx/miis/decca.h"
#include "gfx/miis/bossman.h"
#include "gfx/miis/mantratronic.h"
//haujobb
#include "gfx/miis/xxx.h"
#include "gfx/miis/docd.h"
//tuhb
#include "gfx/miis/watcher.h"
//hooy-program
#include "gfx/miis/gasman.h"
//logicoma
#include "gfx/miis/hoffman.h"
#include "gfx/miis/wobble.h"
#include "gfx/miis/ferris.h"
//t$ + sunspire
#include "gfx/miis/ts.h"
#include "gfx/miis/sunspire.h"
//svatg
#include "gfx/miis/halcy.h"
#include "gfx/miis/sagamusix.h"
#include "gfx/miis/poro.h"
//scenept
#include "gfx/miis/jeenio.h"
#include "gfx/miis/ps.h"
//credits
#include "gfx/miis/tobach.h"
#include "gfx/miis/violet.h"
#include "gfx/miis/targz.h"
#include "gfx/miis/molive.h"
#include "gfx/miis/crypt.h"

#include "groups.h"
#include "demochoon_mp3.h"

#define PI 3.14159265359
#define DEBUG 0

float theta=0, a=0, gt=0, dtm=0, vt1=0, vt2=20;
float l1=0, l2=0, zval=0, zval2=0, tval=0, tval2=0, ha=0;

int gv=0, t1=0, t2=0, scn=0;

f32 plasarray[11][11][11];
f32 scy;

GRRLIB_texImg *radical;
GRRLIB_texImg *skateracc;
GRRLIB_texImg *radicaltext;
GRRLIB_texImg *tex_font;

//miis
//atw
GRRLIB_texImg *mii_losso;
//bitshifters
GRRLIB_texImg *mii_kieran;
GRRLIB_texImg *mii_pmalin;
//rift
GRRLIB_texImg *mii_jtruk;
GRRLIB_texImg *mii_decca;
GRRLIB_texImg *mii_bossman;
GRRLIB_texImg *mii_mantra;
//haujobb
GRRLIB_texImg *mii_xxx;
GRRLIB_texImg *mii_docd;
//tuhb
GRRLIB_texImg *mii_watcher;
//hprg
GRRLIB_texImg *mii_gasman;
//logicoma
GRRLIB_texImg *mii_hoffman;
GRRLIB_texImg *mii_wobble;
GRRLIB_texImg *mii_ferris;
//tssp
GRRLIB_texImg *mii_ts;
GRRLIB_texImg *mii_sunspire;
//svatg
GRRLIB_texImg *mii_halcy;
GRRLIB_texImg *mii_sagamsx;
GRRLIB_texImg *mii_poro;
//scenept
GRRLIB_texImg *mii_ps;
GRRLIB_texImg *mii_jeenio;
//credits
GRRLIB_texImg *mii_tobach;
GRRLIB_texImg *mii_violet;
GRRLIB_texImg *mii_targz;
GRRLIB_texImg *mii_molive;
GRRLIB_texImg *mii_crypt;

f32 cubes[64][3];

f32 heartpos[8][3];

u32 col;

GRRLIB_texImg* (*sceners[21])={&mii_losso,&mii_pmalin,&mii_kieran,&mii_jtruk,&mii_decca,&mii_bossman,&mii_mantra,&mii_xxx,&mii_docd,&mii_watcher,&mii_gasman,&mii_hoffman,&mii_wobble,&mii_ferris,&mii_ts,&mii_sunspire,&mii_halcy,&mii_sagamsx,&mii_poro,&mii_jeenio,&mii_ps};

char (*groups[10])[5][48]= {&attn,&btshft,&rift,&hajb,&tuhb,&hprg,&lgcma,&tssp,&svatg,&scnpt};

char miioffset[]={0,1,3,7,9,10,13,15,18,20};
char miiindex;

int rad2deg(float angle){
	//radical, yo!
	return angle*180/PI;
}

float deg2rad(int angle){
	return (PI/180)*angle;
}

/*
void modeldraw(){
	
	//GRRLIB_SetBackgroundColour(0x55, 0x55, 0x55, 0xFF);

	GRRLIB_3dMode(0.1,1000,90,0,0);
	GRRLIB_ObjectView(0,0,0,0,-a/2,0,2,2,2);

	//GRRLIB_SetLightDiff(1,(guVector){0.0f,0.0f,12.0f},20.0f,8.0f,0xFFFFFFFF);

	GX_Begin(GX_TRIANGLES, GX_VTXFMT0, 2901);
		for(int i=0; i<sizeof(modelNbFace)*3; i+=3){
			GX_Position3f32(modelPos[modelFac[0][i]-1].x,modelPos[modelFac[0][i]-1].y,modelPos[modelFac[0][i]-1].z);
			GX_Normal3f32(modelNom[modelFac[0][i]-1].x,modelNom[modelFac[0][i]-1].y,modelNom[modelFac[0][i]-1].z);
			GX_Color1u32(0xFFFFFFFF);

			GX_Position3f32(modelPos[modelFac[0][i+1]-1].x,modelPos[modelFac[0][i+1]-1].y,modelPos[modelFac[0][i+1]-1].z);
			GX_Normal3f32(modelNom[modelFac[0][i+1]-1].x,modelNom[modelFac[0][i+1]-1].y,modelNom[modelFac[0][i+1]-1].z);
			GX_Color1u32(0xFFFFFFFF);

			GX_Position3f32(modelPos[modelFac[0][i+2]-1].x,modelPos[modelFac[0][i+2]-1].y,modelPos[modelFac[0][i+2]-1].z);
			GX_Normal3f32(modelNom[modelFac[0][i+2]-1].x,modelNom[modelFac[0][i+2]-1].y,modelNom[modelFac[0][i+2]-1].z);
			GX_Color1u32(0xFFFFFFFF);
		}
	GX_End();


	GX_Begin(GX_TRIANGLES, GX_VTXFMT0, modelNbFace * 3);
	col=0xFFFFFFFF;
	for(int i=0; i<modelNbFace; i++) {

		if (i%3==1){ 
			col=0xaaaaaaff;
		} else {
			col=0x444444ff;
		}


		GX_Position3f32(modelPos[modelFac[i][0]-1].x,   modelPos[modelFac[i][0]-1].y,   modelPos[modelFac[i][0]-1].z);
		//GX_Normal3f32(  modelNom[modelNId[i][0]-1].x,   modelNom[modelNId[i][0]-1].y,   modelNom[modelNId[i][0]-1].z);
		GX_Color1u32(col);

		GX_Position3f32(modelPos[modelFac[i][1]-1].x,   modelPos[modelFac[i][1]-1].y,   modelPos[modelFac[i][1]-1].z);
		//GX_Normal3f32(  modelNom[modelNId[i][1]-1].x,   modelNom[modelNId[i][1]-1].y,   modelNom[modelNId[i][1]-1].z);
		GX_Color1u32(col);

		GX_Position3f32(modelPos[modelFac[i][2]-1].x,   modelPos[modelFac[i][2]-1].y,   modelPos[modelFac[i][2]-1].z);
		//GX_Normal3f32(  modelNom[modelNId[i][2]-1].x,   modelNom[modelNId[i][2]-1].y,   modelNom[modelNId[i][2]-1].z);
		GX_Color1u32(col);
		
	}

	GX_End();

	a+=0.5f;

}
*/

void grouptext(){

	GRRLIB_3dMode(0.1, 35, 90, 0, 1);

	GRRLIB_SetLightDiff(1,(guVector){0.0f,0.0f,0.0f},20.0f,2.0f,0xFFFFFFFF);

/*
	float theta=-0.2;

	for (float y=0; y<5; y++){
		for (float x=0; x<39; x++){
			if(grp_slipstream[(int)y*39+(int)x]){
				float fx=(x-(39/2))*cos(theta)+(y-(2.5f))*-sin(theta);
				float fy=(x-(39/2))*sin(theta)+(y-(2.5f))*cos(theta);
				//float fx = x;
				//float fy = y;
				float rotang=rad2deg(theta);
				GRRLIB_ObjectView(fx,-fy,-3,0,0,-rotang,1,1,1);
				GRRLIB_DrawCube(1,1,0xFFFFFFFF);//size, filled, color
			}
		}
	}
*/
	a+=0.5;
}

void cubetunnel(){

		GRRLIB_2dMode();
		for(float i=0; i<576; i++){
			GRRLIB_Line(0,i,640,i,RGBA(128+sin(i/17+a/7)*sin(i/32+a/4)*127,0,255,100));
		}

		GRRLIB_3dMode(0.1, 35, 90, 0, 1);

		GRRLIB_SetLightDiff(0,(guVector){sin(l1)*4.0f,0.0f,cos(l1)*4.0f},20.0f,2.0f,RGBA(64,32,255,255));
		//GRRLIB_ObjectView(sin(l1)*4.0f,0.0f,cos(l1)*4.0f, 0,0,0,1,1,1);
		//GRRLIB_DrawSphere(0.2f, 20, 20, true, 0xFFFFFFFF);

		GRRLIB_SetLightDiff(1,(guVector){0.0f,sin(l2)*4.0f,cos(l2)*4.0f},20.0f,2.0f,RGBA(255,32,64,255));
		//GRRLIB_ObjectView(0.0f,sin(l2)*4.0f,cos(l2)*4.0f, 0,0,0,1,1,1);
		//GRRLIB_DrawSphere(0.2f, 20, 20, true, 0xFFFFFFFF);

		l1+=0.05f;
		l2+=0.03f;

		tval+=0.5f;
		tval2+=0.5f;

		for (float y=0; y<50; y++){
			for (float x=0; x<18; x++){
				zval = y+tval/5;
				GRRLIB_ObjectView(sin(x/PI*1.1)*4+cos(a/7+y/4),cos(x/PI*1.1)*4+sin(a/8+y/4),zval,0,0,-x*(2*PI)*PI,1,1,1);
				GRRLIB_DrawCube(0.5,1,0xFFFFFFFF);//size, filled, color
			}
		}
		for (float y=0; y<50; y++){
			for (float x=0; x<18; x++){
				zval2 = y+tval2/5 - 50;
				GRRLIB_ObjectView(sin(x/PI*1.1)*4+cos(a/7+y/4),cos(x/PI*1.1)*4+sin(a/8+y/4),zval2,0,0,-x*(2*PI)*PI,1,1,1);
				GRRLIB_DrawCube(0.5,1,0xFFFFFFFF);//size, filled, color
			}
		}

		GRRLIB_2dMode();

		GRRLIB_DrawImg (650-295+sin(a/4)*4, 520-315+cos(a/3)*4, radical, 0, 0.75, 0.85, 0x11111180);
		GRRLIB_DrawImg (650-300+sin(a/4)*4, 520-320+cos(a/3)*4, radical, 0, 0.75, 0.85, 0xFFFFFFFF);
		
		GRRLIB_DrawImg (-20+cos(a/3)*4, 80+sin(a/2)*4, radicaltext, -25, 1, 1, 0xFFFFFFFF);

		//GRRLIB_Printf(420, 20, tex_font, 0xFFFFFFFF, 1, "%F", zval);
		//GRRLIB_Printf(420, 40, tex_font, 0xFFFFFFFF, 1, "%F", zval2);

		if (zval2>24) tval2=0;
		if (zval>74) tval=0;

		a+=0.5f;
}

void voxeltest(){

	GRRLIB_2dMode();
	for(float i=0; i<640; i++){
		GRRLIB_Line(i,0,i,528,RGBA(128+sin(i/32+a/13)*sin(i/46+sin(a/24)*8)*127,0,255,100));
	}

	GRRLIB_3dMode(0.1, 35, 90, 0, 1);

	GRRLIB_SetBackgroundColour(0x22, 0x22, 0x22, 0xFF);
   
	GRRLIB_SetLightDiff(1,(guVector){0.0f,0.0f,0.0f},20.0f,2.0f,0xFFFFFFFF);
	GRRLIB_SetLightDiff(2,(guVector){5.0f,5.0f,5.0f},20.0f,2.0f,RGBA(200,0,100,255));
	GRRLIB_SetLightDiff(3,(guVector){-5.0f,-5.0f,-5.0f},20.0f,2.0f,RGBA(100,0,200,255));
	
	GRRLIB_SetLightDiff(4,(guVector){0.0f+sin(a/32)*8,0.0f,0.0f+cos(a/32)*8},1.0f,0.4f,RGBA(255,255,255,255));
	//GRRLIB_SetLightAmbient(0xFFFFFFFF);
	
	GRRLIB_Camera3dSettings(0.0f+sin(a/32)*8,0.0f+sin(a/64)*2,0.0f+cos(a/32)*8, 0,1,0, 0,0,0);

	//GRRLIB_Camera3dSettings(0.0f,3.0f,5.0f, 0,1,0, 0,0,0);

	for(f32 z=-5; z<6; z++){
		for(f32 y=-5; y<6; y++){
			for(f32 x=-5; x<6; x++){
				f32 sv = 1.0f+sin(x/4+a/8)*sin(y/3+z/2+a/13)*1.9f;
				if(sv<0.5) sv=0;
				plasarray[(int)x+4][(int)y+4][(int)z+4]=sv;
				GRRLIB_ObjectView(x/1.5f,y/1.5f+sin(z/4+a/8)/2,z/1.5f,0,0,0,1,1,1);

				GRRLIB_DrawCube(plasarray[(int)x+4][(int)y+4][(int)z+4]/4,1,RGBA(255,255,255,128));//size, filled, color
				//GRRLIB_DrawSphere(plasarray[(int)x+4][(int)y+4][(int)z+4]/4,3,3,1,0xffffffff);
			}
		}
	}

	if (vt1>=20){
		vt2-=0.1f;
		if (vt2<=0) vt2=0;
		for (float y=0; y<5; y++){
			for (float x=0; x<48*4; x++){
				GRRLIB_ObjectView(sin(x/PI/(8.72*1.12))*6,-0.4+y/4-scy-vt2,cos(x/PI/(8.72*1.12))*6, 0,x*((0.675/1.12)*PI),0, 1,1,0.1);
				float cs=slp_small[(int)-y+4][(int)x%48];
				if(cs!=0) cs=0.29;
				GRRLIB_DrawCube(cs,1,RGBA(255,0,255,255));//size, filled, color
			}
		}
	}

	//GRRLIB_2dMode();
	//GRRLIB_DrawImg (650-295+sin(a/4)*4, 520-315+cos(a/3)*4, skateracc, 0, 0.75, 0.85, 0x11111180);

	vt1+=0.1f;

	//scy-=0.1f;
	//if (scy>0) scy=0;

	a+=0.5f;

}

void scroller(){
	GRRLIB_2dMode();
	for(float i=0; i<960; i++){
		GRRLIB_Line(0,i,640,-240+i,RGBA(128+sin(i/48+a/3)*sin(i/33+a/13)*127,0,255,100));
	}

	GRRLIB_3dMode(0.1, 35, 90, 0, 1);
	GRRLIB_SetLightDiff(1,(guVector){0.0f,0.0f,10.0f},20.0f,1.0f,0xffffffff);

	float theta=0.785/2;

	for (int i=4; i<64; i++){
		//if (cubes[i][0]<=0) cubes[i][0]=0;
		GRRLIB_ObjectView(fmod((cubes[i][0]-a*(i/2)*8)/64-82, 83)+40,-20+cubes[i][1],-16+cubes[i][2] ,a*i+3,a*i+3,a*i+3, 1,1,1);
		if (i%2==0){
			GRRLIB_DrawCube(1,1,RGBA(100,0,255,255-i*2));//size, filled, color
		}else{
			GRRLIB_DrawCube(1,1,RGBA(255,0,100,255-i*2));//size, filled, color
		}
	}

	for (float y=0; y<8; y++){
		for (float x=0; x<512; x++){
			int cs=scrolltext_1[(int)-y+7][(int)x%512];
			if (cs!=0){
				float fx=(x*1.5-(39/2))*cos(theta)+(y-(2.5f))*-sin(theta);
				float fy=(x*1.5-(39/2))*sin(theta)+(y-(2.5f))*cos(theta);
				//float fx = (x-(39/2));
				//float fy = y+-3+sin(y/4+x/4+a);

				//ehhhhh close enough :-)
				GRRLIB_ObjectView(40+fx-a*4,15+fy-a*1.65,-4+sin(x/4+a/2)*2 ,0,0,45/2, 1.5,1,0.5f);
				GRRLIB_DrawCube(1,1,RGBA(255,255,255,255));//size, filled, color
			}
		}
	}

	GRRLIB_2dMode();
	int tv=((int)a*32);
	
	if (tv<=640){
		GRRLIB_Rectangle(0,0,640-(a*32),576,0x000000ff,1);
	}

	a+=0.125f;
}

void greets(){
	if (gv<10){
		GRRLIB_2dMode();
		for(float i=0; i<320; i++){
			GRRLIB_Line(i,0,i,576,RGBA(128+sin(i/48+a/2)*127,0,255,100));
			GRRLIB_Line(i+320,0,i+320,576,RGBA(128+sin(i/48-a/2+PI-0.4f)*127,0,255,100));
		}

		GRRLIB_3dMode(0.1, 35, 90, 0, 1);
		GRRLIB_Camera3dSettings(0.0f,0.0f,13.0f, 0,1,0, 0,0,0);
		//GRRLIB_SetLightDiff(1,(guVector){0.0f,0.0f,10.0f},20.0f,1.0f,0xffffffff);

		for (float y=0; y<5; y++){
			for (float x=0; x<48; x++){
				GRRLIB_ObjectView(x-23,-y+20+(sin(gt/3+1.566666)*5)+(sin(x/2+gt)/4)*3,-5, 0,0,0, 1,1,0.25f);
				float cs=(*(groups[gv]))[(int)y][(int)x];
				//GRRLIB_DrawCube(cs,1,RGBA(128+sin(x+gt)*32,0,x*4,255));//size, filled, color
				GRRLIB_DrawCube(cs,1,RGBA(255,128+(y*16),128+(y*16),255));
			}
		}

		GRRLIB_2dMode();
		float mv = 580/2+80+sin(gt/3+1.566666)*190;
		/*fix all this shit at some point as well*/
		switch(gv){
			case 0:
				GRRLIB_DrawImg(640/2-128, mv, (*(sceners[0])), sin(gt/3)*20, 1, 1.25, 0xFFFFFFFF);
				break;
			case 1:
				GRRLIB_DrawImg(340/2-128, mv, (*(sceners[1])), sin(gt/3+1)*20, 1, 1.25, 0xFFFFFFFF);
				GRRLIB_DrawImg(940/2-128, mv, (*(sceners[2])), sin(gt/3+2)*20, 1, 1.25, 0xFFFFFFFF);
				break;
			case 2:
				GRRLIB_DrawImg(140/2-128, mv, (*(sceners[3])), sin(gt/3+1)*20, 1, 1.25, 0xFFFFFFFF);
				GRRLIB_DrawImg(440/2-128, mv, (*(sceners[4])), sin(gt/3+2)*20, 1, 1.25, 0xFFFFFFFF);
				GRRLIB_DrawImg(780/2-128, mv, (*(sceners[5])), sin(gt/3+3)*20, 1, 1.25, 0xFFFFFFFF);
				GRRLIB_DrawImg(1140/2-128, mv, (*(sceners[6])), sin(gt/3+4)*20, 1, 1.25, 0xFFFFFFFF);
				break;
			case 3:
				GRRLIB_DrawImg(340/2-128, mv, (*(sceners[7])), sin(gt/3+1)*20, 1, 1.25, 0xFFFFFFFF);
				GRRLIB_DrawImg(940/2-128, mv, (*(sceners[8])), sin(gt/3+2)*20, 1, 1.25, 0xFFFFFFFF);
				break;
			case 4:
				GRRLIB_DrawImg(640/2-128, mv, (*(sceners[9])), sin(gt/3)*20, 1, 1.25, 0xFFFFFFFF);
				break;
			case 5:
				GRRLIB_DrawImg(640/2-128, mv, (*(sceners[10])), sin(gt/3)*20, 1, 1.25, 0xFFFFFFFF);
				break;
			case 6:
				GRRLIB_DrawImg(240/2-128, mv, (*(sceners[11])), sin(gt/3+1)*20, 1, 1.25, 0xFFFFFFFF);
				GRRLIB_DrawImg(640/2-128, mv, (*(sceners[12])), sin(gt/3+2)*20, 1, 1.25, 0xFFFFFFFF);
				GRRLIB_DrawImg(1040/2-128, mv, (*(sceners[13])), sin(gt/3+3)*20, 1, 1.25, 0xFFFFFFFF);
				break;
			case 7:
				GRRLIB_DrawImg(340/2-128, mv, (*(sceners[14])), sin(gt/3+1)*20, 1, 1.25, 0xFFFFFFFF);
				GRRLIB_DrawImg(940/2-128, mv, (*(sceners[15])), sin(gt/3+2)*20, 1, 1.25, 0xFFFFFFFF);
				break;
			case 8:
				GRRLIB_DrawImg(240/2-128, mv, (*(sceners[16])), sin(gt/3+1)*20, 1, 1.25, 0xFFFFFFFF);
				GRRLIB_DrawImg(640/2-128, mv, (*(sceners[17])), sin(gt/3+2)*20, 1, 1.25, 0xFFFFFFFF);
				GRRLIB_DrawImg(1040/2-128, mv, (*(sceners[18])), sin(gt/3+3)*20, 1, 1.25, 0xFFFFFFFF);
				break;
			case 9:
				GRRLIB_DrawImg(340/2-128, mv, (*(sceners[19])), sin(gt/3+1)*20, 1, 1.25, 0xFFFFFFFF);
				GRRLIB_DrawImg(940/2-128, mv, (*(sceners[20])), sin(gt/3+2)*20, 1, 1.25, 0xFFFFFFFF);
				break;

		}
		//GRRLIB_DrawImg(640/2, 480/2-100, skateracc, 0, 1.75, 2, 0xFFFFFFFF);
		//GRRLIB_DrawImg(640/2-128, 480/2+80+sin(gt/3+1.566666)*200, (*(sceners[gv])), sin(gt/3)*20, 1, 1.25, 0xFFFFFFFF);
		//GRRLIB_Printf(20,20,tex_font,0xffffffff,1,"%F", gt);

		gt+=0.085f;
		if (gt>(6*PI)){
			gt=0;
			gv+=1;
		}
		a+=0.1f;
	}
}

void endscreen(){
	GRRLIB_2dMode();
	for(float i=0; i<600; i++){
		GRRLIB_Line(0,i,640,i,RGBA(128+sin(i/48+a/3)*sin(i/33+a/13)*127,0,255,100));
	}

	GRRLIB_3dMode(0.1, 35, 90, 0, 1);
	//GRRLIB_SetLightDiff(1,(guVector){0.0f,0.0f,10.0f},20.0f,1.0f,0xffffffff);

	for (float y=0; y<5; y++){
		for (float x=0; x<40; x++){
			GRRLIB_ObjectView(x/1.25-15,-y/1.25+15+sin(x/4+a/3)/4,-4, 0,0,0, 0.8,0.8,0.15f);
			float cs=grp_slipstream[(int)y][(int)x];
			GRRLIB_DrawCube(cs,1,RGBA(255,128+(y*16),128+(y*16),255));//size, filled, color
		}
	}

	for (float i=0; i<3; i++){
		for (float y=0; y<5; y++){
			for (float x=0; x<27; x++){
				GRRLIB_ObjectView(x/2-20+(i*10),-y/2+8+sin(x/4+a/3+i)/4,-4, 0,0,0, 0.5,0.5,0.25f);
				float cs=credits[(int)i][(int)y][(int)x];
				GRRLIB_DrawCube(cs,1,RGBA(255,128+(y*16),128+(y*16),255));//size, filled, color
			}
		}
	}

	for (float y=0; y<5; y++){
		for (float x=0; x<13; x++){
			GRRLIB_ObjectView(x/2+4,-y/2+sin(x/4+a/3)/4,-4, 0,0,0, 0.5,0.5,0.25f);
			float cs=credits[1][(int)y][(int)x];
			GRRLIB_DrawCube(cs,1,RGBA(255,128+(y*16),128+(y*16),255));//size, filled, color
		}
	}

	for (float y=0; y<5; y++){
		for (float x=0; x<27; x++){
			GRRLIB_ObjectView(x/2-20,-y/2-7+sin(x/4+a/3)/4,-4, 0,0,0, 0.5,0.5,0.25f);
			float cs=credits[3][(int)y][(int)x];
			GRRLIB_DrawCube(cs,1,RGBA(255,128+(y*16),128+(y*16),255));//size, filled, color
		}
	}

	for (float i=0; i<3; i++){
		for (float y=0; y<5; y++){
			for (float x=0; x<27; x++){
				GRRLIB_ObjectView(x/3-20+(i*14),-y/3-12+sin(x/4+a/3+i)/4,-4, 0,0,0, 0.4,0.4,0.1);
				float cs=support[(int)i][(int)y][(int)x];
				GRRLIB_DrawCube(cs,1,RGBA(255,128+(y*16),128+(y*16),255));//size, filled, color
			}
		}
	}

	for (float y=0; y<5; y++){
		for (float x=0; x<27; x++){
			GRRLIB_ObjectView(x/3+6,-y/3+4+sin(x/4+a/3)/4,-4, 0,0,0, 0.4,0.4,0.1);
			float cs=tbch[(int)y][(int)x];
			GRRLIB_DrawCube(cs,1,RGBA(255,128+(y*16),128+(y*16),255));//size, filled, color
		}
	}

	for (float y=0; y<5; y++){
		for (float x=0; x<27; x++){
			GRRLIB_ObjectView(x/3+6,-y/3-4+sin(x/4+a/3)/4,-4, 0,0,0, 0.4,0.4,0.1);
			float cs=violt[(int)y][(int)x];
			GRRLIB_DrawCube(cs,1,RGBA(255,128+(y*16),128+(y*16),255));//size, filled, color
		}
	}

	GRRLIB_2dMode();

	GRRLIB_DrawImg(450, 60, mii_tobach, sin(a/3)*10, 0.4, 0.5, 0xFFFFFFFF);
	GRRLIB_DrawImg(450, 180, mii_violet, sin(a/3+2)*10, 0.4, 0.5, 0xFFFFFFFF);
	GRRLIB_DrawImg(40, 330, mii_targz, sin(a/3+4)*10, 0.35, 0.4, 0xFFFFFFFF);
	GRRLIB_DrawImg(265, 330, mii_molive, sin(a/3+6)*10, 0.35, 0.4, 0xFFFFFFFF);
	GRRLIB_DrawImg(450, 330, mii_crypt, sin(a/3+8)*10, 0.35, 0.4, 0xFFFFFFFF);


	a+=0.1f;
}

void drawheart(float hx, float hz, float angle, int col){
	for (float y=-4; y<4; y++){
		for (float x=-4; x<5; x++){
			float fx=(x*cos(angle)+(y*-sin(angle)));
			float fy=(x*sin(angle)+(y*cos(angle)));
			//radical B-)
			float heartang=rad2deg(angle);
			GRRLIB_ObjectView(hx+fx,-fy,hz, 0,0,-heartang, 1,1,1);
			float cs=heart[(int)y+4][(int)x+4];
			GRRLIB_DrawCube(cs,1,RGBA(255,170+col,170+col,128));//size, filled, color
		}
	}
}

void hearts(){

	GRRLIB_2dMode();
	for(float i=0; i<288; i++){
		GRRLIB_Line(0,i,640,i,RGBA(128+sin(i/48+a/3)*127,0,255,100));
		GRRLIB_Line(0,i+288,640,i+288,RGBA(128+sin(i/48-a/3+(PI+0.4f))*127,0,255,100));
	}

	GRRLIB_3dMode(0.1, 35, 90, 0, 1);
	GRRLIB_SetLightDiff(1,(guVector){0.0f,0.0f,10.0f},20.0f,1.0f,0xffffffff);

	for (float i=0; i<5; i++){
		heartpos[(int)i][1]-=0.25f;
		if (heartpos[(int)i][1]<=-15) heartpos[(int)i][1]=25;
		drawheart(0,0-heartpos[(int)i][1],sin(ha/8+i/4)*2,i*16);
	}

	GRRLIB_2dMode();

	GRRLIB_DrawImg(370+sin(a/4)*4, 240+cos(a/3)*4, skateracc, 0, 1.5, 1.5, 0x11111180);
	GRRLIB_DrawImg(375+sin(a/4)*4, 245+cos(a/3)*4, skateracc, 0, 1.5, 1.5, 0xFFFFFFFF);

	a+=0.5f;
	ha+=0.1f;

}

int main() {

	srand(time(NULL));

	for (int i=0; i<64; i++){
		cubes[i][0]=rand()%80;
		cubes[i][1]=rand()%60;
		cubes[i][2]=rand()%10;
	}

	for (int i=0; i<8; i++){
		heartpos[i][1]=(float)i*8;
	}

	GRRLIB_Init();
	WPAD_Init();

	ASND_Init();
	MP3Player_Init();

	GRRLIB_texImg *tex_font = GRRLIB_LoadTexture(font);
	GRRLIB_InitTileSet(tex_font, 16, 16, 32);

	radical = GRRLIB_LoadTexture(tubular);

	skateracc = GRRLIB_LoadTexture(raccoon);

	radicaltext = GRRLIB_LoadTexture(tubulartext);

	GRRLIB_Settings.antialias = false;

	//miis
	/*fix all this shit before release*/
	mii_losso = GRRLIB_LoadTexture(losso);
	mii_pmalin = GRRLIB_LoadTexture(pmalin);
	mii_kieran = GRRLIB_LoadTexture(kieran);
	mii_jtruk = GRRLIB_LoadTexture(jtruk);
	mii_decca = GRRLIB_LoadTexture(decca);
	mii_bossman = GRRLIB_LoadTexture(bossman);
	mii_mantra = GRRLIB_LoadTexture(mantratronic);
	mii_xxx = GRRLIB_LoadTexture(xxx);
	mii_docd = GRRLIB_LoadTexture(docd);
	mii_watcher = GRRLIB_LoadTexture(watcher);
	mii_gasman = GRRLIB_LoadTexture(gasman);
	mii_hoffman = GRRLIB_LoadTexture(hoffman);
	mii_wobble = GRRLIB_LoadTexture(wobble);
	mii_ferris = GRRLIB_LoadTexture(ferris);
	mii_ts = GRRLIB_LoadTexture(ts);
	mii_sunspire = GRRLIB_LoadTexture(sunspire);
	mii_halcy = GRRLIB_LoadTexture(halcy);
	mii_sagamsx = GRRLIB_LoadTexture(sagamusix);
	mii_poro = GRRLIB_LoadTexture(poro);
	mii_ps = GRRLIB_LoadTexture(ps);
	mii_jeenio = GRRLIB_LoadTexture(jeenio);
	mii_tobach = GRRLIB_LoadTexture(tobach);
	mii_violet = GRRLIB_LoadTexture(violet);
	mii_targz = GRRLIB_LoadTexture(targz);
	mii_molive = GRRLIB_LoadTexture(molive);
	mii_crypt = GRRLIB_LoadTexture(crypt);

	GRRLIB_SetHandle(mii_losso,128,128);
	GRRLIB_SetHandle(mii_pmalin,128,128);
	GRRLIB_SetHandle(mii_kieran,128,128);
	GRRLIB_SetHandle(mii_jtruk,128,128);
	GRRLIB_SetHandle(mii_decca,128,128);
	GRRLIB_SetHandle(mii_bossman,128,128);
	GRRLIB_SetHandle(mii_mantra,128,128);
	GRRLIB_SetHandle(mii_xxx,128,128);
	GRRLIB_SetHandle(mii_docd,128,128);
	GRRLIB_SetHandle(mii_watcher,128,128);
	GRRLIB_SetHandle(mii_gasman,128,128);
	GRRLIB_SetHandle(mii_hoffman,128,128);
	GRRLIB_SetHandle(mii_wobble,128,128);
	GRRLIB_SetHandle(mii_ferris,128,128);
	GRRLIB_SetHandle(mii_ts,128,128);
	GRRLIB_SetHandle(mii_sunspire,128,128);
	GRRLIB_SetHandle(mii_halcy,128,128);
	GRRLIB_SetHandle(mii_sagamsx,128,128);
	GRRLIB_SetHandle(mii_poro,128,128);
	GRRLIB_SetHandle(mii_ps,128,128);
	GRRLIB_SetHandle(mii_jeenio,128,128);
	GRRLIB_SetHandle(mii_tobach,128,128);
	GRRLIB_SetHandle(mii_violet,128,128);
	GRRLIB_SetHandle(mii_targz,128,128);
	GRRLIB_SetHandle(mii_molive,128,128);
	GRRLIB_SetHandle(mii_crypt,128,128);

	//scy = -10;

	GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
	GRRLIB_Camera3dSettings(0.0f,0.0f,13.0f, 0,1,0, 0,0,0);
	GRRLIB_SetLightAmbient(0x333333FF);

	//choons innit
	if (!DEBUG) MP3Player_PlayBuffer(demochoon_mp3, demochoon_mp3_size, NULL);

	while(1) {

		GRRLIB_2dMode();
		WPAD_ScanPads();
		if(WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) exit(0);

		//scroller();
		//cubetunnel();
		//voxeltest();
		//greets();
		//endscreen();
		//hearts();

		if (!DEBUG){
			dtm+=1.0f/50;

			if (dtm>=0 && dtm<=30){
				scroller();
			}else if (dtm>=30 && dtm<=45){
				cubetunnel();
			}else if(dtm>=45 && dtm<=66){
				voxeltest();
			}else if (dtm>=66 && dtm<=110){
				greets();
			}else if (dtm>=110 && dtm<=128){
				hearts();
			}else if (dtm>=128){
				endscreen();
			}
		

			GRRLIB_2dMode();

			if (dtm>=29 && dtm<=33){
				GRRLIB_Rectangle(640-t1,0,660,576,RGBA(0,0,0,255),1);
				t1+=12;
			}
			if (dtm>=44 && dtm<=48){
				GRRLIB_Rectangle(640-t2,0,660,576,RGBA(0,0,0,255),1);
				t2+=12;
			}
		};
		
		GRRLIB_Render();
	}
	GRRLIB_FreeTexture(tex_font);
	GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB

	exit(0);
}