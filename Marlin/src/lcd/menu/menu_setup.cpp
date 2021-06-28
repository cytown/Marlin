/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

// MiniTree 小树定制固件，新增调机菜单
// Setup Menu
//


#include "../../inc/MarlinConfigPre.h"

#if HAS_LCD_MENU

#include "menu_item.h"
#include "../../module/motion.h"
#include "../../module/planner.h"
#include "../../module/stepper.h"
#include "../../MarlinCore.h"


#ifdef MiniTreeFunc // MiniTree.h

#define VALUE_ITEM(MSG, VALUE, STYL)    do{ char msg[21]; strcpy_P(msg, PSTR(": ")); strcpy(msg + 2, VALUE); STATIC_ITEM(MSG, STYL, msg); }while(0)

// MiniTree 小树定制固件，修改电机方向后立刻应用，并保存到eeprom
void update_invert_dir() {
	  stepper.set_directions();
	  ui.store_settings();
}
// MiniTree 小树定制固件 电机方向菜单
void menu_invert_dir() {

  START_MENU();
  BACK_ITEM(MSG_SETUP);

  EDIT_ITEM(bool2, MSG_X_INVERT_DIR, &planner.settings.invert_dir[X_AXIS], update_invert_dir);  //X电机方向
  EDIT_ITEM(bool2, MSG_Y_INVERT_DIR, &planner.settings.invert_dir[Y_AXIS], update_invert_dir);  //Y电机方向
  EDIT_ITEM(bool2, MSG_Z_INVERT_DIR, &planner.settings.invert_dir[Z_AXIS], update_invert_dir);  //Z电机方向
  EDIT_ITEM(bool2, MSG_E_INVERT_DIR, &planner.settings.invert_dir[E_AXIS], update_invert_dir);  //挤出机电机方向

  END_MENU();
}

// MiniTree 小树定制固件，修改旋钮方向后立刻保存到eeprom
void update_encoder_dir() {
	  ui.store_settings();
}

#ifdef USE_XMIN_PLUG
  static bool x_min_status = (READ(X_MIN_PIN) != X_MIN_ENDSTOP_INVERTING ? true : false);
#endif
#ifdef USE_XMAX_PLUG
  static bool x_max_status = (READ(X_MAX_PIN) != X_MAX_ENDSTOP_INVERTING ? true : false);
#endif
#ifdef USE_YMIN_PLUG
  static bool y_min_status = (READ(Y_MIN_PIN) != Y_MIN_ENDSTOP_INVERTING ? true : false);
#endif
#ifdef USE_YMAX_PLUG
  static bool y_max_status = (READ(Y_MAX_PIN) != Y_MAX_ENDSTOP_INVERTING ? true : false);
#endif
#ifdef USE_ZMIN_PLUG
  static bool z_min_status = (READ(Z_MIN_PIN) != Z_MIN_ENDSTOP_INVERTING ? true : false);
#endif
#ifdef USE_ZMAX_PLUG
  static bool z_max_status = (READ(Z_MAX_PIN) != Z_MAX_ENDSTOP_INVERTING ? true : false);
#endif

// 刷新限位状态
void refresh_endstops(){
  #ifdef USE_XMIN_PLUG
    x_min_status = (READ(X_MIN_PIN) != X_MIN_ENDSTOP_INVERTING ? true : false);
  #endif
  #ifdef USE_XMAX_PLUG
    x_max_status = (READ(X_MAX_PIN) != X_MAX_ENDSTOP_INVERTING ? true : false);
  #endif
  #ifdef USE_YMIN_PLUG
    y_min_status = (READ(Y_MIN_PIN) != Y_MIN_ENDSTOP_INVERTING ? true : false);
  #endif
  #ifdef USE_YMAX_PLUG
    y_max_status = (READ(Y_MAX_PIN) != Y_MAX_ENDSTOP_INVERTING ? true : false);
  #endif
  #ifdef USE_ZMIN_PLUG
    z_min_status = (READ(Z_MIN_PIN) != Z_MIN_ENDSTOP_INVERTING ? true : false);
  #endif
  #ifdef USE_ZMAX_PLUG
    z_max_status = (READ(Z_MAX_PIN) != Z_MAX_ENDSTOP_INVERTING ? true : false);
  #endif
}

// MiniTree 小树定制固件 限位状态菜单
void menu_endstop_status() {
  START_MENU();
  BACK_ITEM(MSG_SETUP);
  refresh_endstops();
  #ifdef USE_XMIN_PLUG
    EDIT_ITEM(bool3, MSG_X_MIN_STATUS, &x_min_status, refresh_endstops);
  #endif
  #ifdef USE_XMAX_PLUG
    EDIT_ITEM(bool3, MSG_X_MAX_STATUS, &x_max_status, refresh_endstops);
  #endif
  #ifdef USE_YMIN_PLUG
    EDIT_ITEM(bool3, MSG_Y_MIN_STATUS, &y_min_status, refresh_endstops);
  #endif
  #ifdef USE_YMAX_PLUG
    EDIT_ITEM(bool3, MSG_Y_MAX_STATUS, &y_max_status, refresh_endstops);
  #endif
  #ifdef USE_ZMIN_PLUG
    EDIT_ITEM(bool3, MSG_Z_MIN_STATUS, &z_min_status, refresh_endstops);
  #endif
  #ifdef USE_ZMAX_PLUG
    EDIT_ITEM(bool3, MSG_Z_MAX_STATUS, &z_max_status, refresh_endstops);
  #endif
  //ui.refresh();
  END_MENU();
}

// MiniTree 小树定制固件 调机主菜单
void menu_setup() {
  START_MENU();
  BACK_ITEM(MSG_MAIN);
  //电机方向子菜单
  SUBMENU(MSG_INVERT_DIR, menu_invert_dir);
  //旋钮方向修改
  EDIT_ITEM(bool2, MSG_ENCODER_DIR, &ui.encoder_dir, update_encoder_dir);
  //限位状态子菜单
  SUBMENU(MSG_ENDSTOP_STATUS, menu_endstop_status);
  //软限位开关
  EDIT_ITEM(bool, MSG_LCD_SOFT_ENDSTOPS, &soft_endstop._enabled);
  //冷挤出保护开关
  EDIT_ITEM(bool, MSG_ALLOW_COLD_EXTRUDE, &thermalManager.allow_cold_extrude);
  //初始化eeprom选项
  CONFIRM_ITEM(MSG_INIT_EEPROM,
    MSG_BUTTON_INIT, MSG_BUTTON_CANCEL,
    ui.init_eeprom, nullptr,
    GET_TEXT(MSG_INIT_EEPROM), (const char *)nullptr, PSTR("?")
  );

  END_MENU();
}

#endif // MiniTreeFunc

#endif
