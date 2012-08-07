/*
 * This software is licensed under the terms of the MIT-License
 * See COPYING for further information. 
 * ---
 * Copyright (C) 2011, Lukas Weber <laochailan@web.de>
 * Copyright (C) 2012, Alexeyew Andrew <http://akari.thebadasschoobs.org/>
 */

#include <time.h>
#include "savereplay.h"
#include "options.h"
#include "global.h"
#include "replay.h"
#include "plrmodes.h"

void save_rpy(void *a) {
	Replay *rpy = &global.replay;
	char strtime[128], name[128];
	time_t rawtime;
	struct tm * timeinfo;
	
	// time when the game was *initiated*
	rawtime = (time_t)rpy->stages[0].seed;
	timeinfo = localtime(&rawtime);
	strftime(strtime, 128, "%Y%m%d_%H-%M-%S_%Z", timeinfo);
	
	char prepr[16];
	plrmode_repr(prepr, 16, rpy->stages[0].plr_char, rpy->stages[0].plr_shot);
	
	if(rpy->stgcount > 1)
		snprintf(name, 128, "taisei_%s_%s", prepr, strtime);
	else
		snprintf(name, 128, "taisei_stg%d_%s_%s", rpy->stages[0].stage, prepr, strtime);
	
	replay_save(rpy, name);
	if(a) ((MenuData*)a)->quit = 2;
}

void dont_save_rpy(void *a) {
	((MenuData*)a)->quit = 2;
}

void create_saverpy_menu(MenuData *m) {
	create_menu(m);
	m->type = MT_Persistent;
	m->title = "Save replay?";
	
	add_menu_entry(m, "Yes",	save_rpy,		m);
	add_menu_entry(m, "No",		dont_save_rpy,	m);
}

void draw_saverpy_menu(MenuData *m) {
	draw_options_menu_bg(m);
	
	glPushMatrix();
	glTranslatef(SCREEN_W/2, SCREEN_H/2 - 100, 0);
	draw_text(AL_Center, 0, 0, m->title, _fonts.mainmenu);
	glTranslatef(0, 100, 0);
	
	int i; for(i = 0; i < m->ecount; i++) {
		MenuEntry *e = &(m->entries[i]);
		
		e->drawdata += 0.2 * (10*(i == m->cursor) - e->drawdata);
		float a = e->drawdata * 0.1;
		
		if(e->action == NULL)
			glColor4f(0.5, 0.5, 0.5, 0.5);
		else {
			float ia = 1-a;
			glColor4f(0.9 + ia * 0.1, 0.6 + ia * 0.4, 0.2 + ia * 0.8, 0.7 + 0.3 * a);
		}
		
		if(e->name)
			draw_text(AL_Center, -50 + 100 * i, 0, e->name, _fonts.mainmenu);
	}
	
	glPopMatrix();
	
	fade_out(m->fade);
}

int saverpy_menu_loop(MenuData *m) {
	return menu_loop(m, NULL, draw_saverpy_menu);
}
