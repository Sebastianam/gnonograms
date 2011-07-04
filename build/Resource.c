/* Resource.c generated by valac 0.11.6, the Vala compiler
 * generated from Resource.vala, do not modify */

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
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <glib/gi18n-lib.h>

#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

#define TYPE_CONFIG (config_get_type ())
#define CONFIG(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_CONFIG, Config))
#define CONFIG_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_CONFIG, ConfigClass))
#define IS_CONFIG(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_CONFIG))
#define IS_CONFIG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_CONFIG))
#define CONFIG_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_CONFIG, ConfigClass))

typedef struct _Config Config;
typedef struct _ConfigClass ConfigClass;
#define _config_unref0(var) ((var == NULL) ? NULL : (var = (config_unref (var), NULL)))

#define TYPE_GAME_STATE (game_state_get_type ())

#define TYPE_CELL_STATE (cell_state_get_type ())

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


extern gint resource_MAXROWSIZE;
gint resource_MAXROWSIZE = 100;
extern gint resource_MAXCOLSIZE;
gint resource_MAXCOLSIZE = 100;
extern gint resource_MAXGRADE;
gint resource_MAXGRADE = 10;
extern gint resource_MAXTRIES;
gint resource_MAXTRIES = 30;
extern gint resource_MINFONTSIZE;
gint resource_MINFONTSIZE = 6;
extern gint resource_MAXFONTSIZE;
gint resource_MAXFONTSIZE = 16;
extern gchar* resource_font_desc;
gchar* resource_font_desc = NULL;
extern gdouble resource_CELLOFFSET_NOGRID;
gdouble resource_CELLOFFSET_NOGRID = 0.0;
extern gdouble resource_CELLOFFSET_WITHGRID;
gdouble resource_CELLOFFSET_WITHGRID = 2.0;
extern gdouble* resource_MINORGRIDDASH;
extern gint resource_MINORGRIDDASH_length1;
gdouble* resource_MINORGRIDDASH = NULL;
gint resource_MINORGRIDDASH_length1 = 0;
extern GdkColor* resource_colors;
extern gint resource_colors_length1;
extern gint resource_colors_length2;
GdkColor* resource_colors = NULL;
gint resource_colors_length1 = 0;
gint resource_colors_length2 = 0;
extern gchar* resource_exec_dir;
gchar* resource_exec_dir = NULL;
extern gchar* resource_resource_dir;
gchar* resource_resource_dir = NULL;
extern gchar* resource_locale_dir;
gchar* resource_locale_dir = NULL;
extern gchar* resource_game_dir;
gchar* resource_game_dir = NULL;
extern gchar* resource_game_name;
gchar* resource_game_name = NULL;
extern gchar* resource_icon_dir;
gchar* resource_icon_dir = NULL;
extern gchar* resource_mallard_manual_dir;
gchar* resource_mallard_manual_dir = NULL;
extern gchar* resource_html_manual_dir;
gchar* resource_html_manual_dir = NULL;
extern gchar* resource_prefix;
gchar* resource_prefix = NULL;
extern gboolean resource_installed;
gboolean resource_installed = FALSE;

#define RESOURCE_APP_GETTEXT_PACKAGE GETTEXT_PACKAGE
#define RESOURCE_DEFAULTGAMENAME "New game"
#define RESOURCE_GAMEFILEEXTENSION ".gno"
#define RESOURCE_POSITIONFILENAME "currentposition"
#define RESOURCE_BLOCKSEPARATOR ","
void resource_init (const gchar* arg0);
gboolean resource_is_installed (const gchar* exec_dir);
gpointer config_ref (gpointer instance);
void config_unref (gpointer instance);
GParamSpec* param_spec_config (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_config (GValue* value, gpointer v_object);
void value_take_config (GValue* value, gpointer v_object);
gpointer value_get_config (const GValue* value);
GType config_get_type (void) G_GNUC_CONST;
Config* config_get_instance (void);
gchar* config_get_game_dir (Config* self, const gchar* defaultdir);
gchar* config_get_game_name (Config* self, const gchar* defaultname);
GType game_state_get_type (void) G_GNUC_CONST;
GType cell_state_get_type (void) G_GNUC_CONST;
gchar** config_get_colors (Config* self, int* result_length1);
gchar* resource_get_langpack_dir (void);
void resource_set_colors (void);
void resource_set_font (void);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);


static gchar* bool_to_string (gboolean self) {
	gchar* result = NULL;
	if (self) {
		gchar* _tmp0_;
		_tmp0_ = g_strdup ("true");
		result = _tmp0_;
		return result;
	} else {
		gchar* _tmp1_;
		_tmp1_ = g_strdup ("false");
		result = _tmp1_;
		return result;
	}
}


void resource_init (const gchar* arg0) {
	gchar* _tmp0_;
	gchar* _tmp1_;
	gchar* _tmp2_ = NULL;
	gchar* _tmp3_;
	GFile* _tmp4_ = NULL;
	GFile* _tmp5_;
	GFile* exec_file;
	GFile* _tmp6_ = NULL;
	GFile* _tmp7_;
	gchar* _tmp8_ = NULL;
	gchar* _tmp9_;
	gboolean _tmp10_;
	gchar* _tmp11_ = NULL;
	gchar* _tmp12_;
	gchar* _tmp13_ = NULL;
	gchar* _tmp23_;
	gchar* _tmp24_;
	gchar* _tmp25_ = NULL;
	gchar* _tmp34_;
	gchar* _tmp35_;
	gchar* _tmp36_;
	gchar* _tmp37_;
	gchar* _tmp38_;
	Config* _tmp39_ = NULL;
	Config* _tmp40_;
	gchar* _tmp41_;
	gchar* _tmp42_ = NULL;
	gchar* _tmp43_;
	Config* _tmp44_ = NULL;
	Config* _tmp45_;
	gchar* _tmp46_ = NULL;
	gchar* _tmp47_;
	GdkColor* _tmp48_ = NULL;
	GdkColor* _tmp49_;
	gint setting;
	GdkColor _tmp50_ = {0};
	GdkColor _tmp51_ = {0};
	GdkColor _tmp52_ = {0};
	GdkColor _tmp53_ = {0};
	gint solving;
	GdkColor _tmp54_ = {0};
	GdkColor _tmp55_ = {0};
	GdkColor _tmp56_ = {0};
	GdkColor _tmp57_ = {0};
	Config* _tmp58_ = NULL;
	Config* _tmp59_;
	gint _tmp60_;
	gchar** _tmp61_ = NULL;
	gchar** _tmp62_;
	gchar** config_colors;
	gint config_colors_length1;
	gint _config_colors_size_;
	GdkColor _tmp63_ = {0};
	GdkColor _tmp64_ = {0};
	GdkColor _tmp65_ = {0};
	GdkColor _tmp66_ = {0};
	gchar* _tmp67_;
	gchar* _tmp68_;
	gdouble* _tmp69_ = NULL;
	gdouble* _tmp70_;
	g_return_if_fail (arg0 != NULL);
	_tmp0_ = g_strdup (_PREFIX);
	_tmp1_ = _tmp0_;
	_g_free0 (resource_prefix);
	resource_prefix = _tmp1_;
	fprintf (stdout, "Prefix is %s \n", resource_prefix);
	fprintf (stdout, "gettext package is %s \n", RESOURCE_APP_GETTEXT_PACKAGE);
	_tmp2_ = g_find_program_in_path (arg0);
	_tmp3_ = _tmp2_;
	_tmp4_ = g_file_new_for_path (_tmp3_);
	exec_file = (_tmp5_ = _tmp4_, _g_free0 (_tmp3_), _tmp5_);
	_tmp6_ = g_file_get_parent (exec_file);
	_tmp7_ = _tmp6_;
	_tmp8_ = g_file_get_path (_tmp7_);
	_tmp9_ = _tmp8_;
	_g_free0 (resource_exec_dir);
	resource_exec_dir = _tmp9_;
	_g_object_unref0 (_tmp7_);
	fprintf (stdout, "Exec_dir is %s \n", resource_exec_dir);
	_tmp10_ = resource_is_installed (resource_exec_dir);
	resource_installed = _tmp10_;
	_tmp11_ = bool_to_string (resource_installed);
	_tmp12_ = _tmp11_;
	fprintf (stdout, "Is installed is %s\n", _tmp12_);
	_g_free0 (_tmp12_);
	if (resource_installed) {
		GFile* _tmp14_ = NULL;
		GFile* _tmp15_;
		GFile* _tmp16_ = NULL;
		GFile* _tmp17_;
		gchar* _tmp18_ = NULL;
		gchar* _tmp19_;
		gchar* _tmp20_;
		_tmp14_ = g_file_get_parent (exec_file);
		_tmp15_ = _tmp14_;
		_tmp16_ = g_file_get_parent (_tmp15_);
		_tmp17_ = _tmp16_;
		_tmp18_ = g_file_get_path (_tmp17_);
		_tmp19_ = _tmp18_;
		_tmp20_ = g_strconcat (_tmp19_, "/share/gnonograms", NULL);
		_g_free0 (_tmp13_);
		_tmp13_ = _tmp20_;
		_g_free0 (_tmp19_);
		_g_object_unref0 (_tmp17_);
		_g_object_unref0 (_tmp15_);
	} else {
		gchar* _tmp21_;
		gchar* _tmp22_;
		_tmp21_ = g_strdup (resource_exec_dir);
		_tmp22_ = _tmp21_;
		_g_free0 (_tmp13_);
		_tmp13_ = _tmp22_;
	}
	_tmp23_ = g_strdup (_tmp13_);
	_tmp24_ = _tmp23_;
	_g_free0 (resource_resource_dir);
	resource_resource_dir = _tmp24_;
	fprintf (stdout, "Resource_dir is %s \n", resource_resource_dir);
	if (resource_installed) {
		GFile* _tmp26_ = NULL;
		GFile* _tmp27_;
		GFile* _tmp28_ = NULL;
		GFile* _tmp29_;
		gchar* _tmp30_ = NULL;
		gchar* _tmp31_;
		gchar* _tmp32_;
		_tmp26_ = g_file_get_parent (exec_file);
		_tmp27_ = _tmp26_;
		_tmp28_ = g_file_get_parent (_tmp27_);
		_tmp29_ = _tmp28_;
		_tmp30_ = g_file_get_path (_tmp29_);
		_tmp31_ = _tmp30_;
		_tmp32_ = g_strconcat (_tmp31_, "/share/locale", NULL);
		_g_free0 (_tmp25_);
		_tmp25_ = _tmp32_;
		_g_free0 (_tmp31_);
		_g_object_unref0 (_tmp29_);
		_g_object_unref0 (_tmp27_);
	} else {
		gchar* _tmp33_;
		_tmp33_ = g_strconcat (resource_resource_dir, "/locale", NULL);
		_g_free0 (_tmp25_);
		_tmp25_ = _tmp33_;
	}
	_tmp34_ = g_strdup (_tmp25_);
	_tmp35_ = _tmp34_;
	_g_free0 (resource_locale_dir);
	resource_locale_dir = _tmp35_;
	fprintf (stdout, "Locale_dir is %s \n", resource_locale_dir);
	_tmp36_ = g_strconcat (resource_resource_dir, "/icons", NULL);
	_g_free0 (resource_icon_dir);
	resource_icon_dir = _tmp36_;
	_tmp37_ = g_strconcat (resource_resource_dir, "/mallard", NULL);
	_g_free0 (resource_mallard_manual_dir);
	resource_mallard_manual_dir = _tmp37_;
	_tmp38_ = g_strconcat (resource_resource_dir, "/html", NULL);
	_g_free0 (resource_html_manual_dir);
	resource_html_manual_dir = _tmp38_;
	_tmp39_ = config_get_instance ();
	_tmp40_ = _tmp39_;
	_tmp41_ = g_strconcat (resource_resource_dir, "/games", NULL);
	_tmp42_ = config_get_game_dir (_tmp40_, _tmp41_);
	_tmp43_ = _tmp42_;
	_g_free0 (resource_game_dir);
	resource_game_dir = _tmp43_;
	_g_free0 (_tmp41_);
	_config_unref0 (_tmp40_);
	_tmp44_ = config_get_instance ();
	_tmp45_ = _tmp44_;
	_tmp46_ = config_get_game_name (_tmp45_, RESOURCE_DEFAULTGAMENAME);
	_tmp47_ = _tmp46_;
	_g_free0 (resource_game_name);
	resource_game_name = _tmp47_;
	_config_unref0 (_tmp45_);
	_tmp48_ = g_new0 (GdkColor, 2 * 4);
	_tmp49_ = _tmp48_;
	resource_colors = (g_free (resource_colors), NULL);
	resource_colors_length1 = 2;
	resource_colors_length2 = 4;
	resource_colors = _tmp49_;
	setting = (gint) GAME_STATE_SETTING;
	gdk_color_parse ("GREY", &_tmp50_);
	resource_colors[(setting * resource_colors_length2) + ((gint) CELL_STATE_UNKNOWN)] = _tmp50_;
	gdk_color_parse ("WHITE", &_tmp51_);
	resource_colors[(setting * resource_colors_length2) + ((gint) CELL_STATE_EMPTY)] = _tmp51_;
	gdk_color_parse ("BLACK", &_tmp52_);
	resource_colors[(setting * resource_colors_length2) + ((gint) CELL_STATE_FILLED)] = _tmp52_;
	gdk_color_parse ("RED", &_tmp53_);
	resource_colors[(setting * resource_colors_length2) + ((gint) CELL_STATE_ERROR)] = _tmp53_;
	solving = (gint) GAME_STATE_SOLVING;
	gdk_color_parse ("GREY", &_tmp54_);
	resource_colors[(solving * resource_colors_length2) + ((gint) CELL_STATE_UNKNOWN)] = _tmp54_;
	gdk_color_parse ("YELLOW", &_tmp55_);
	resource_colors[(solving * resource_colors_length2) + ((gint) CELL_STATE_EMPTY)] = _tmp55_;
	gdk_color_parse ("BLUE", &_tmp56_);
	resource_colors[(solving * resource_colors_length2) + ((gint) CELL_STATE_FILLED)] = _tmp56_;
	gdk_color_parse ("RED", &_tmp57_);
	resource_colors[(solving * resource_colors_length2) + ((gint) CELL_STATE_ERROR)] = _tmp57_;
	_tmp58_ = config_get_instance ();
	_tmp59_ = _tmp58_;
	_tmp61_ = config_get_colors (_tmp59_, &_tmp60_);
	config_colors = (_tmp62_ = _tmp61_, _config_unref0 (_tmp59_), _tmp62_);
	config_colors_length1 = _tmp60_;
	_config_colors_size_ = _tmp60_;
	gdk_color_parse (config_colors[0], &_tmp63_);
	resource_colors[(setting * resource_colors_length2) + ((gint) CELL_STATE_EMPTY)] = _tmp63_;
	gdk_color_parse (config_colors[1], &_tmp64_);
	resource_colors[(setting * resource_colors_length2) + ((gint) CELL_STATE_FILLED)] = _tmp64_;
	gdk_color_parse (config_colors[2], &_tmp65_);
	resource_colors[(solving * resource_colors_length2) + ((gint) CELL_STATE_EMPTY)] = _tmp65_;
	gdk_color_parse (config_colors[3], &_tmp66_);
	resource_colors[(solving * resource_colors_length2) + ((gint) CELL_STATE_FILLED)] = _tmp66_;
	_tmp67_ = g_strdup ("Ariel");
	_tmp68_ = _tmp67_;
	_g_free0 (resource_font_desc);
	resource_font_desc = _tmp68_;
	_tmp69_ = g_new0 (gdouble, 2);
	_tmp69_[0] = 0.5;
	_tmp69_[1] = 3.0;
	_tmp70_ = _tmp69_;
	resource_MINORGRIDDASH = (g_free (resource_MINORGRIDDASH), NULL);
	resource_MINORGRIDDASH_length1 = 2;
	resource_MINORGRIDDASH = _tmp70_;
	config_colors = (_vala_array_free (config_colors, config_colors_length1, (GDestroyNotify) g_free), NULL);
	_g_free0 (_tmp25_);
	_g_free0 (_tmp13_);
	_g_object_unref0 (exec_file);
}


gboolean resource_is_installed (const gchar* exec_dir) {
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_;
	g_return_val_if_fail (exec_dir != NULL, FALSE);
	_tmp1_ = g_str_has_prefix (exec_dir, resource_prefix);
	if (_tmp1_) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = FALSE;
	}
	result = _tmp0_;
	return result;
}


gchar* resource_get_langpack_dir (void) {
	gchar* result = NULL;
	gchar* _tmp0_;
	_tmp0_ = g_strdup (resource_locale_dir);
	result = _tmp0_;
	return result;
}


void resource_set_colors (void) {
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	GtkDialog* _tmp2_ = NULL;
	GtkDialog* dialog;
	const gchar* _tmp3_ = NULL;
	GtkLabel* _tmp4_ = NULL;
	GtkLabel* fset_label;
	const gchar* _tmp5_ = NULL;
	GtkLabel* _tmp6_ = NULL;
	GtkLabel* eset_label;
	const gchar* _tmp7_ = NULL;
	GtkLabel* _tmp8_ = NULL;
	GtkLabel* fsolve_label;
	const gchar* _tmp9_ = NULL;
	GtkLabel* _tmp10_ = NULL;
	GtkLabel* esolve_label;
	GtkVBox* _tmp11_ = NULL;
	GtkVBox* label_box;
	GdkColor _tmp12_;
	GtkColorButton* _tmp13_ = NULL;
	GtkColorButton* filled_setting;
	const gchar* _tmp14_ = NULL;
	GdkColor _tmp15_;
	GtkColorButton* _tmp16_ = NULL;
	GtkColorButton* empty_setting;
	const gchar* _tmp17_ = NULL;
	GdkColor _tmp18_;
	GtkColorButton* _tmp19_ = NULL;
	GtkColorButton* filled_solving;
	const gchar* _tmp20_ = NULL;
	GdkColor _tmp21_;
	GtkColorButton* _tmp22_ = NULL;
	GtkColorButton* empty_solving;
	const gchar* _tmp23_ = NULL;
	GtkVBox* _tmp24_ = NULL;
	GtkVBox* button_box;
	GtkHBox* _tmp25_ = NULL;
	GtkHBox* hbox;
	gint _tmp26_;
	_tmp0_ = _ ("Ok");
	_tmp1_ = _ ("Cancel");
	_tmp2_ = (GtkDialog*) gtk_dialog_new_with_buttons (NULL, NULL, GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, _tmp0_, GTK_RESPONSE_OK, _tmp1_, GTK_RESPONSE_CANCEL, NULL);
	dialog = g_object_ref_sink (_tmp2_);
	_tmp3_ = _ ("Color of filled cell when setting");
	_tmp4_ = (GtkLabel*) gtk_label_new (_tmp3_);
	fset_label = g_object_ref_sink (_tmp4_);
	_tmp5_ = _ ("Color of empty cell when setting");
	_tmp6_ = (GtkLabel*) gtk_label_new (_tmp5_);
	eset_label = g_object_ref_sink (_tmp6_);
	_tmp7_ = _ ("Color of filled cell when solving");
	_tmp8_ = (GtkLabel*) gtk_label_new (_tmp7_);
	fsolve_label = g_object_ref_sink (_tmp8_);
	_tmp9_ = _ ("Color of empty cell when solving");
	_tmp10_ = (GtkLabel*) gtk_label_new (_tmp9_);
	esolve_label = g_object_ref_sink (_tmp10_);
	_tmp11_ = (GtkVBox*) gtk_vbox_new (FALSE, 5);
	label_box = g_object_ref_sink (_tmp11_);
	gtk_container_add (GTK_CONTAINER (label_box), GTK_WIDGET (fset_label));
	gtk_container_add (GTK_CONTAINER (label_box), GTK_WIDGET (eset_label));
	gtk_container_add (GTK_CONTAINER (label_box), GTK_WIDGET (fsolve_label));
	gtk_container_add (GTK_CONTAINER (label_box), GTK_WIDGET (esolve_label));
	_tmp13_ = (GtkColorButton*) gtk_color_button_new_with_color ((_tmp12_ = resource_colors[(((gint) GAME_STATE_SETTING) * resource_colors_length2) + ((gint) CELL_STATE_FILLED)], &_tmp12_));
	filled_setting = g_object_ref_sink (_tmp13_);
	_tmp14_ = _ ("Color of filled cell when setting");
	gtk_color_button_set_title (filled_setting, _tmp14_);
	_tmp16_ = (GtkColorButton*) gtk_color_button_new_with_color ((_tmp15_ = resource_colors[(((gint) GAME_STATE_SETTING) * resource_colors_length2) + ((gint) CELL_STATE_EMPTY)], &_tmp15_));
	empty_setting = g_object_ref_sink (_tmp16_);
	_tmp17_ = _ ("Color of empty cell when setting");
	gtk_color_button_set_title (empty_setting, _tmp17_);
	_tmp19_ = (GtkColorButton*) gtk_color_button_new_with_color ((_tmp18_ = resource_colors[(((gint) GAME_STATE_SOLVING) * resource_colors_length2) + ((gint) CELL_STATE_FILLED)], &_tmp18_));
	filled_solving = g_object_ref_sink (_tmp19_);
	_tmp20_ = _ ("Color of filled cell when solving");
	gtk_color_button_set_title (filled_solving, _tmp20_);
	_tmp22_ = (GtkColorButton*) gtk_color_button_new_with_color ((_tmp21_ = resource_colors[(((gint) GAME_STATE_SOLVING) * resource_colors_length2) + ((gint) CELL_STATE_EMPTY)], &_tmp21_));
	empty_solving = g_object_ref_sink (_tmp22_);
	_tmp23_ = _ ("Color of empty cell when solving");
	gtk_color_button_set_title (empty_solving, _tmp23_);
	_tmp24_ = (GtkVBox*) gtk_vbox_new (FALSE, 5);
	button_box = g_object_ref_sink (_tmp24_);
	gtk_container_add (GTK_CONTAINER (button_box), GTK_WIDGET (filled_setting));
	gtk_container_add (GTK_CONTAINER (button_box), GTK_WIDGET (empty_setting));
	gtk_container_add (GTK_CONTAINER (button_box), GTK_WIDGET (filled_solving));
	gtk_container_add (GTK_CONTAINER (button_box), GTK_WIDGET (empty_solving));
	_tmp25_ = (GtkHBox*) gtk_hbox_new (FALSE, 5);
	hbox = g_object_ref_sink (_tmp25_);
	gtk_container_add (GTK_CONTAINER (hbox), GTK_WIDGET (label_box));
	gtk_container_add (GTK_CONTAINER (hbox), GTK_WIDGET (button_box));
	gtk_container_add (GTK_CONTAINER (dialog->vbox), GTK_WIDGET (hbox));
	gtk_widget_show_all (GTK_WIDGET (dialog));
	_tmp26_ = gtk_dialog_run (dialog);
	if (_tmp26_ == GTK_RESPONSE_OK) {
		GdkColor _tmp27_ = {0};
		GdkColor _tmp28_ = {0};
		GdkColor _tmp29_ = {0};
		GdkColor _tmp30_ = {0};
		gtk_color_button_get_color (filled_setting, &_tmp27_);
		resource_colors[(((gint) GAME_STATE_SETTING) * resource_colors_length2) + ((gint) CELL_STATE_FILLED)] = _tmp27_;
		gtk_color_button_get_color (empty_setting, &_tmp28_);
		resource_colors[(((gint) GAME_STATE_SETTING) * resource_colors_length2) + ((gint) CELL_STATE_EMPTY)] = _tmp28_;
		gtk_color_button_get_color (filled_solving, &_tmp29_);
		resource_colors[(((gint) GAME_STATE_SOLVING) * resource_colors_length2) + ((gint) CELL_STATE_FILLED)] = _tmp29_;
		gtk_color_button_get_color (empty_solving, &_tmp30_);
		resource_colors[(((gint) GAME_STATE_SOLVING) * resource_colors_length2) + ((gint) CELL_STATE_EMPTY)] = _tmp30_;
	}
	gtk_object_destroy (GTK_OBJECT (dialog));
	_g_object_unref0 (hbox);
	_g_object_unref0 (button_box);
	_g_object_unref0 (empty_solving);
	_g_object_unref0 (filled_solving);
	_g_object_unref0 (empty_setting);
	_g_object_unref0 (filled_setting);
	_g_object_unref0 (label_box);
	_g_object_unref0 (esolve_label);
	_g_object_unref0 (fsolve_label);
	_g_object_unref0 (eset_label);
	_g_object_unref0 (fset_label);
	_g_object_unref0 (dialog);
}


void resource_set_font (void) {
	GtkFontSelectionDialog* _tmp0_ = NULL;
	GtkFontSelectionDialog* dialog;
	gint _tmp1_;
	_tmp0_ = (GtkFontSelectionDialog*) gtk_font_selection_dialog_new ("Select font used for the clues");
	dialog = g_object_ref_sink (_tmp0_);
	_tmp1_ = gtk_dialog_run (GTK_DIALOG (dialog));
	if (_tmp1_ != GTK_RESPONSE_CANCEL) {
		const gchar* _tmp2_ = NULL;
		gchar* _tmp3_;
		gchar* _tmp4_;
		_tmp2_ = gtk_font_selection_dialog_get_font_name (dialog);
		_tmp3_ = g_strdup (_tmp2_);
		_tmp4_ = _tmp3_;
		_g_free0 (resource_font_desc);
		resource_font_desc = _tmp4_;
	}
	gtk_object_destroy (GTK_OBJECT (dialog));
	_g_object_unref0 (dialog);
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}



