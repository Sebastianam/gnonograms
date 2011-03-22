/* main.c generated by valac 0.11.6, the Vala compiler
 * generated from main.vala, do not modify */

/*  Copyright (C) 2010-2011  Jeremy Wootten
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 * As a special exception, if you use inline functions from this file, this
 * file does not by itself cause the resulting executable to be covered by
 * the GNU Lesser General Public License.
 * 
 *  Author:
 * 	Jeremy Wootten <jeremwootten@gmail.com>
 */

#include <glib.h>
#include <glib-object.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib/gi18n-lib.h>


#define TYPE_GAME_STATE (game_state_get_type ())

#define TYPE_CELL_STATE (cell_state_get_type ())

#define TYPE_GNONOGRAM_FILETYPE (gnonogram_filetype_get_type ())

#define TYPE_CELL (cell_get_type ())
typedef struct _Cell Cell;

#define TYPE_BUTTON_PRESS (button_press_get_type ())

#define TYPE_GNONOGRAM_CONTROLLER (gnonogram_controller_get_type ())
#define GNONOGRAM_CONTROLLER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GNONOGRAM_CONTROLLER, Gnonogram_controller))
#define GNONOGRAM_CONTROLLER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GNONOGRAM_CONTROLLER, Gnonogram_controllerClass))
#define IS_GNONOGRAM_CONTROLLER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GNONOGRAM_CONTROLLER))
#define IS_GNONOGRAM_CONTROLLER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GNONOGRAM_CONTROLLER))
#define GNONOGRAM_CONTROLLER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GNONOGRAM_CONTROLLER, Gnonogram_controllerClass))

typedef struct _Gnonogram_controller Gnonogram_controller;
typedef struct _Gnonogram_controllerClass Gnonogram_controllerClass;
#define _gnonogram_controller_unref0(var) ((var == NULL) ? NULL : (var = (gnonogram_controller_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

typedef enum  {
	GAME_STATE_SETTING,
	GAME_STATE_SOLVING
} GameState;

typedef enum  {
	CELL_STATE_UNKNOWN,
	CELL_STATE_EMPTY,
	CELL_STATE_FILLED,
	CELL_STATE_ERROR,
	CELL_STATE_COMPLETED
} CellState;

typedef enum  {
	GNONOGRAM_FILETYPE_GAME,
	GNONOGRAM_FILETYPE_POSITION
} Gnonogram_FileType;

struct _Cell {
	gint row;
	gint col;
	CellState state;
};

typedef enum  {
	BUTTON_PRESS_LEFT_SINGLE,
	BUTTON_PRESS_LEFT_DOUBLE,
	BUTTON_PRESS_MIDDLE_SINGLE,
	BUTTON_PRESS_MIDDLE_DOUBLE,
	BUTTON_PRESS_RIGHT_SINGLE,
	BUTTON_PRESS_RIGHT_DOUBLE,
	BUTTON_PRESS_UNDEFINED
} ButtonPress;



GType game_state_get_type (void) G_GNUC_CONST;
GType cell_state_get_type (void) G_GNUC_CONST;
GType gnonogram_filetype_get_type (void) G_GNUC_CONST;
GType cell_get_type (void) G_GNUC_CONST;
Cell* cell_dup (const Cell* self);
void cell_free (Cell* self);
gboolean cell_changed (Cell *self, gint r, gint c);
void cell_copy (Cell *self, Cell* b);
GType button_press_get_type (void) G_GNUC_CONST;
gint _vala_main (gchar** args, int args_length1);
void resource_init (const gchar* arg0);
#define RESOURCE_APP_GETTEXT_PACKAGE GETTEXT_PACKAGE
gchar* resource_get_langpack_dir (void);
Gnonogram_controller* gnonogram_controller_new (gint r, gint c);
Gnonogram_controller* gnonogram_controller_construct (GType object_type, gint r, gint c);
gpointer gnonogram_controller_ref (gpointer instance);
void gnonogram_controller_unref (gpointer instance);
GParamSpec* param_spec_gnonogram_controller (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_gnonogram_controller (GValue* value, gpointer v_object);
void value_take_gnonogram_controller (GValue* value, gpointer v_object);
gpointer value_get_gnonogram_controller (const GValue* value);
GType gnonogram_controller_get_type (void) G_GNUC_CONST;


GType game_state_get_type (void) {
	static volatile gsize game_state_type_id__volatile = 0;
	if (g_once_init_enter (&game_state_type_id__volatile)) {
		static const GEnumValue values[] = {{GAME_STATE_SETTING, "GAME_STATE_SETTING", "setting"}, {GAME_STATE_SOLVING, "GAME_STATE_SOLVING", "solving"}, {0, NULL, NULL}};
		GType game_state_type_id;
		game_state_type_id = g_enum_register_static ("GameState", values);
		g_once_init_leave (&game_state_type_id__volatile, game_state_type_id);
	}
	return game_state_type_id__volatile;
}


GType cell_state_get_type (void) {
	static volatile gsize cell_state_type_id__volatile = 0;
	if (g_once_init_enter (&cell_state_type_id__volatile)) {
		static const GEnumValue values[] = {{CELL_STATE_UNKNOWN, "CELL_STATE_UNKNOWN", "unknown"}, {CELL_STATE_EMPTY, "CELL_STATE_EMPTY", "empty"}, {CELL_STATE_FILLED, "CELL_STATE_FILLED", "filled"}, {CELL_STATE_ERROR, "CELL_STATE_ERROR", "error"}, {CELL_STATE_COMPLETED, "CELL_STATE_COMPLETED", "completed"}, {0, NULL, NULL}};
		GType cell_state_type_id;
		cell_state_type_id = g_enum_register_static ("CellState", values);
		g_once_init_leave (&cell_state_type_id__volatile, cell_state_type_id);
	}
	return cell_state_type_id__volatile;
}


GType gnonogram_filetype_get_type (void) {
	static volatile gsize gnonogram_filetype_type_id__volatile = 0;
	if (g_once_init_enter (&gnonogram_filetype_type_id__volatile)) {
		static const GEnumValue values[] = {{GNONOGRAM_FILETYPE_GAME, "GNONOGRAM_FILETYPE_GAME", "game"}, {GNONOGRAM_FILETYPE_POSITION, "GNONOGRAM_FILETYPE_POSITION", "position"}, {0, NULL, NULL}};
		GType gnonogram_filetype_type_id;
		gnonogram_filetype_type_id = g_enum_register_static ("Gnonogram_FileType", values);
		g_once_init_leave (&gnonogram_filetype_type_id__volatile, gnonogram_filetype_type_id);
	}
	return gnonogram_filetype_type_id__volatile;
}


gboolean cell_changed (Cell *self, gint r, gint c) {
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	if (r != (*self).row) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = c != (*self).col;
	}
	if (_tmp0_) {
		(*self).row = r;
		(*self).col = c;
		result = TRUE;
		return result;
	} else {
		result = FALSE;
		return result;
	}
}


void cell_copy (Cell *self, Cell* b) {
	(*self).row = (*b).row;
	(*self).col = (*b).col;
	(*self).state = (*b).state;
}


Cell* cell_dup (const Cell* self) {
	Cell* dup;
	dup = g_new0 (Cell, 1);
	memcpy (dup, self, sizeof (Cell));
	return dup;
}


void cell_free (Cell* self) {
	g_free (self);
}


GType cell_get_type (void) {
	static volatile gsize cell_type_id__volatile = 0;
	if (g_once_init_enter (&cell_type_id__volatile)) {
		GType cell_type_id;
		cell_type_id = g_boxed_type_register_static ("Cell", (GBoxedCopyFunc) cell_dup, (GBoxedFreeFunc) cell_free);
		g_once_init_leave (&cell_type_id__volatile, cell_type_id);
	}
	return cell_type_id__volatile;
}


GType button_press_get_type (void) {
	static volatile gsize button_press_type_id__volatile = 0;
	if (g_once_init_enter (&button_press_type_id__volatile)) {
		static const GEnumValue values[] = {{BUTTON_PRESS_LEFT_SINGLE, "BUTTON_PRESS_LEFT_SINGLE", "left-single"}, {BUTTON_PRESS_LEFT_DOUBLE, "BUTTON_PRESS_LEFT_DOUBLE", "left-double"}, {BUTTON_PRESS_MIDDLE_SINGLE, "BUTTON_PRESS_MIDDLE_SINGLE", "middle-single"}, {BUTTON_PRESS_MIDDLE_DOUBLE, "BUTTON_PRESS_MIDDLE_DOUBLE", "middle-double"}, {BUTTON_PRESS_RIGHT_SINGLE, "BUTTON_PRESS_RIGHT_SINGLE", "right-single"}, {BUTTON_PRESS_RIGHT_DOUBLE, "BUTTON_PRESS_RIGHT_DOUBLE", "right-double"}, {BUTTON_PRESS_UNDEFINED, "BUTTON_PRESS_UNDEFINED", "undefined"}, {0, NULL, NULL}};
		GType button_press_type_id;
		button_press_type_id = g_enum_register_static ("ButtonPress", values);
		g_once_init_leave (&button_press_type_id__volatile, button_press_type_id);
	}
	return button_press_type_id__volatile;
}


gint _vala_main (gchar** args, int args_length1) {
	gint result = 0;
	gboolean testing;
	gboolean debug;
	gboolean test_column;
	gint test_idx;
	gint _start_rows;
	gint _start_cols;
	gchar* _tmp4_;
	gchar* package_name;
	gchar* _tmp5_ = NULL;
	gchar* langpackdir;
	Gnonogram_controller* _tmp6_ = NULL;
	Gnonogram_controller* _tmp7_;
	testing = FALSE;
	debug = FALSE;
	test_column = FALSE;
	test_idx = -1;
	_start_rows = -1;
	_start_cols = -1;
	{
		gint i;
		i = 1;
		{
			gboolean _tmp0_;
			_tmp0_ = TRUE;
			while (TRUE) {
				if (!_tmp0_) {
					i++;
				}
				_tmp0_ = FALSE;
				if (!(i < args_length1)) {
					break;
				}
				if (g_strcmp0 (args[i], "--test") == 0) {
					testing = TRUE;
					_start_rows = 1;
					_start_cols = 10;
					debug = TRUE;
					continue;
				}
				if (g_strcmp0 (args[i], "--rows") == 0) {
					gint _tmp1_;
					_tmp1_ = atoi (args[i + 1]);
					_start_rows = _tmp1_;
					i++;
					continue;
				}
				if (g_strcmp0 (args[i], "--cols") == 0) {
					gint _tmp2_;
					_tmp2_ = atoi (args[i + 1]);
					_start_cols = _tmp2_;
					i++;
					continue;
				}
				if (g_strcmp0 (args[i], "--debug") == 0) {
					if ((args_length1 - i) >= 2) {
						gint _tmp3_;
						debug = FALSE;
						test_column = g_strcmp0 (args[i + 1], "column") == 0;
						_tmp3_ = atoi (args[i + 2]);
						test_idx = _tmp3_;
					} else {
						debug = TRUE;
					}
					continue;
				}
			}
		}
	}
	resource_init (args[0]);
	gtk_init (&args_length1, &args);
	_tmp4_ = g_strdup (RESOURCE_APP_GETTEXT_PACKAGE);
	package_name = _tmp4_;
	_tmp5_ = resource_get_langpack_dir ();
	langpackdir = _tmp5_;
	bindtextdomain (package_name, langpackdir);
	bind_textdomain_codeset (package_name, "UTF-8");
	textdomain (package_name);
	_tmp6_ = gnonogram_controller_new (_start_rows, _start_cols);
	_tmp7_ = _tmp6_;
	_gnonogram_controller_unref0 (_tmp7_);
	gtk_main ();
	result = 0;
	_g_free0 (langpackdir);
	_g_free0 (package_name);
	return result;
}


int main (int argc, char ** argv) {
	g_type_init ();
	return _vala_main (argv, argc);
}



