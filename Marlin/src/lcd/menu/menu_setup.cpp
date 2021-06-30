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

#define PIN(V, T) V##_##T##_PIN
#define MSG(V, T) MSG_##V##_##T##_STATUS
#define INVERT(V, T) V##_##T##_ENDSTOP_INVERTING
#define READ_STOP_STATUS(V, T) READ(PIN(V, T)) != INVERT(V, T)
#define UPDATE_STOP_STATUS(V, T) _##V##_##T##_status = READ_STOP_STATUS(V, T)
#define MENU_STOP_STATUS(V, T) EDIT_ITEM(bools, MSG(V, T), &_##V##_##T##_status, refresh_endstops, false)

// MiniTree 小树定制固件，修改电机方向后立刻应用，并保存到eeprom
void update_invert_dir() {
	  stepper.set_directions();
	  ui.store_settings();
}
// MiniTree 小树定制固件 电机方向菜单
void menu_invert_dir() {

  START_MENU();
  BACK_ITEM(MSG_SETUP);

  EDIT_ITEM(bools, MSG_X_INVERT_DIR, &planner.extras.invert_dir[X_AXIS], update_invert_dir, true, GET_TEXT(MSG_LCD_Backward), GET_TEXT(MSG_LCD_Forward));  // X电机方向
  EDIT_ITEM(bools, MSG_Y_INVERT_DIR, &planner.extras.invert_dir[Y_AXIS], update_invert_dir, true, GET_TEXT(MSG_LCD_Backward), GET_TEXT(MSG_LCD_Forward));  // Y电机方向
  EDIT_ITEM(bools, MSG_Z_INVERT_DIR, &planner.extras.invert_dir[Z_AXIS], update_invert_dir, true, GET_TEXT(MSG_LCD_Backward), GET_TEXT(MSG_LCD_Forward));  // Z电机方向
  EDIT_ITEM(bools, MSG_E_INVERT_DIR, &planner.extras.invert_dir[E_AXIS], update_invert_dir, true, GET_TEXT(MSG_LCD_Backward), GET_TEXT(MSG_LCD_Forward));  // 挤出机电机方向

  END_MENU();
}

// MiniTree 小树定制固件，修改旋钮方向后立刻保存到eeprom
void update_encoder_dir() {
	  ui.store_settings();
}

#ifdef USE_XMIN_PLUG
  static bool UPDATE_STOP_STATUS(X, MIN);
#endif
#ifdef USE_XMAX_PLUG
  static bool UPDATE_STOP_STATUS(X, MAX);
#endif
#ifdef USE_YMIN_PLUG
  static bool UPDATE_STOP_STATUS(Y, MIN);
#endif
#ifdef USE_YMAX_PLUG
  static bool UPDATE_STOP_STATUS(Y, MAX);
#endif
#ifdef USE_ZMIN_PLUG
  static bool UPDATE_STOP_STATUS(Z, MIN);
#endif
#ifdef USE_ZMAX_PLUG
  static bool UPDATE_STOP_STATUS(Z, MAX);
#endif

// 刷新限位状态
void refresh_endstops(){
  #ifdef USE_XMIN_PLUG
    UPDATE_STOP_STATUS(X, MIN);
  #endif
  #ifdef USE_XMAX_PLUG
    UPDATE_STOP_STATUS(X, MAX;
  #endif
  #ifdef USE_YMIN_PLUG
    UPDATE_STOP_STATUS(Y, MIN);
  #endif
  #ifdef USE_YMAX_PLUG
    UPDATE_STOP_STATUS(Y, MAX);
  #endif
  #ifdef USE_ZMIN_PLUG
    UPDATE_STOP_STATUS(Z, MIN);
  #endif
  #ifdef USE_ZMAX_PLUG
    UPDATE_STOP_STATUS(Z, MAX);
  #endif
}

// MiniTree 小树定制固件 限位状态菜单
void menu_endstop_status() {
  START_MENU();

  BACK_ITEM(MSG_SETUP);
  refresh_endstops();
  #ifdef USE_XMIN_PLUG
    MENU_STOP_STATUS(X, MIN);
  #endif
  #ifdef USE_XMAX_PLUG
    MENU_STOP_STATUS(X, MAX);
  #endif
  #ifdef USE_YMIN_PLUG
    MENU_STOP_STATUS(Y, MIN);
    EDIT_ITEM(bool3, MSG_Y_MIN_STATUS, &y_min_status, refresh_endstops);
  #endif
  #ifdef USE_YMAX_PLUG
    MENU_STOP_STATUS(Y, MAX);
  #endif
  #ifdef USE_ZMIN_PLUG
    MENU_STOP_STATUS(Z, MIN);
  #endif
  #ifdef USE_ZMAX_PLUG
    MENU_STOP_STATUS(Z, MAX);
  #endif

  END_MENU();
}

// MiniTree 小树定制固件 调机主菜单
void menu_setup() {
  START_MENU();

  BACK_ITEM(MSG_MAIN);
  //电机方向子菜单
  SUBMENU(MSG_INVERT_DIR, menu_invert_dir);
  //旋钮方向修改
  EDIT_ITEM(bools, MSG_ENCODER_DIR, &planner.extras.encoder_dir, update_encoder_dir, true, GET_TEXT(MSG_LCD_Backward), GET_TEXT(MSG_LCD_Forward));
  //限位状态子菜单
  SUBMENU(MSG_ENDSTOP_STATUS, menu_endstop_status);
  //软限位开关
  EDIT_ITEM(bool, MSG_LCD_SOFT_ENDSTOPS, &soft_endstop._enabled);
  //冷挤出保护开关
  EDIT_ITEM(bool, MSG_ALLOW_COLD_EXTRUDE, &thermalManager.allow_cold_extrude);

  END_MENU();
}

#endif // MiniTreeFunc

#endif
