/**
 * ===========================================================================
 * ========================= 小 树 定 制 固 件 简 介 =========================
 * ===========================================================================
 * 以后会暂停维护1.x固件
 * 全面启用2.x固件
 * 专用版Arduino可以编译2.x固件 但是vsc更快
 * 以前一直没推广2.x固件 主要是因为vsc环境配置麻烦 例如pio被墙把小白拒之门外
 * 在此感谢院长 制作了 专用版Arduino 此固件只能编译2.x固件 1.x固件报错
 *
 * 继承 屏幕修改电机方向 旋钮方向
 * 继承 软限位 冷挤出等原有功能
 * 继承 修改后自动保存 不必三连操作
 * TMC驱动 失败会显示tmc连接错误，1.x不显示
 * TMC驱动 可以通过屏幕调电流
 * 中文翻译更全面 旧版本“软限位”只能显示“soft限位”
 * 2.x固件占用RAM小 占用flash多
 * 固件做了很多中文注解
 *
 * 修改摘要
 * 增加 中英语言选择菜单前置
 * 增加 回原点Z安全位置 1.x cxy固件不启作用
 * 增加 SD卡打印文件有二次确认  1.x预热时显示文件名
 * 增加 PID屏幕可调
 * 增加 暂停移开喷头 1.x固件默认关闭
 * 增加 对应机型的步进值自动选择
 * 增加 热床限温自动选择 cxy120度 Tx90度
 * 增加 z安全归零自动选择 cxy右上 Tx左下
 * 增加 自动选择双z电机
 * 增加 12864大屏小屏选项
 * 增加 z2电机旋转方向
 * 增加 常开风扇改可控
 * 增加 断料检测前置
 * 增加 直线增强 前置 近程不需要
 * 增加 曲线增强 前置
 *
 * 修改 cxy喷嘴PID 使用南柯参数
 * 修改 所有重定义 全部改为直接定义
 * 修改 打印加速度1000
 * 修改 抖动速度5
 *
 * Update:
 * 2021-06-21  @cytown 重新整理代码，增加了一些huhuzhu的配置
 *
 */

#pragma once


//===========================================================================
//======================= 小 树 定 制 固 件 基 本 配 置 =====================
//===========================================================================

// 定义机型
// T2/T3  = 0
// Corexy = 1
// i3     = 2 稍后完善
#define MiniTreeMachine 1

// 屏幕选择
// 12864大屏 = 0
// 12864小屏 = 1
// TFT35触屏 = 2 稍后完善
#define DisplayScreen 0

//===========================================================================
//======================新手就不要往下看了，开始刷机！=======================
//===========================================================================

// Configuration.h
//=======================

#define STRING_CONFIG_H_AUTHOR "(XenoXue,Cytown MiniTree)"

#define CUSTOM_VERSION_FILE Version.h

// 主板选择 在board.h文件内有支持的主板 可以自行选择
// 小树定制 BOARD_MKS_GEN_L_V21
#define MOTHERBOARD BOARD_MKS_GEN_L_V21

// 使用BLtouch的话需要注释掉这个
//#define BLTOUCH

// TOUCHMI调平 利用光电开关与金属探针/磁铁控制伸缩的一种探针 |小风3D家的TOUCHMI调平精度不错 就是装不好有点废热床|
//#define TOUCH_MI_PROBE

// 小树定制固件，定义机型
// 自定义机器尺寸
#if MiniTreeMachine == 0  // Tx
  #define CUSTOM_MACHINE_NAME "MiniTree Tx"

  #define X_BED_SIZE 120
  #define Y_BED_SIZE 120
  #define Z_MAX_POS  160

  #define BED_MAXTEMP 90

  // 小树定制固件，Tx喷嘴PID温度230度的结果
  #define DEFAULT_Kp  19.67
  #define DEFAULT_Ki  0.67
  #define DEFAULT_Kd  145.30

  // 小树定制固件，T2热床PID温度70度的结果
  #define DEFAULT_bedKp 74.28
  #define DEFAULT_bedKi 1.62
  #define DEFAULT_bedKd 852.36

#elif MiniTreeMachine == 1  // CoreXY
  #define CUSTOM_MACHINE_NAME "MiniTree CoreXY"

  #define X_BED_SIZE 310
  #define Y_BED_SIZE 310
  #define Z_MAX_POS  300

  #define BED_MAXTEMP 120

  // 小树定制固件，Corexy喷嘴PID温度 南柯参数
  #define DEFAULT_Kp  17.05
  #define DEFAULT_Ki  0.55
  #define DEFAULT_Kd  225.05

  // 小树定制固件，Corexy热床PID温度80度的结果
  // XenoXue use: 263.85 51.95 893.40
  // huhuzhu use: 480.34 76.65 805.85
  #define DEFAULT_bedKp  263.85
  #define DEFAULT_bedKi  51.95
  #define DEFAULT_bedKd  893.40

  // 小树定制固件，自动适配机型
  #define COREXY

  // 小树定制固件 corexy的归零限位使用YMAX T3使用YMin
  #define USE_YMAX_PLUG

  // 小树定制固件 步进和脉冲
  // Bmg和Titan=382.165 Z丝杆2导程=1600 4导程=800 8导程=400
  #define DEFAULT_AXIS_STEPS_PER_UNIT   { 80, 80, 1600, 90 }
  // huhuzhu define: 32细分+泰坦挤出机
  //#define DEFAULT_AXIS_STEPS_PER_UNIT   { 160, 160, 3200, 764.331 }

  // 小树定制固件，corexy Y归零点改用max 坐标Y310
  #define Y_HOME_DIR 1

  // z回零下落位置 删除注释开启自定义
  #define Z_SAFE_HOMING_X_POINT 30
  #define Z_SAFE_HOMING_Y_POINT 280

  // 小树定制固件 Corexy停留位置为平台左后方。
  #define NOZZLE_PARK_POINT { (X_MIN_POS + 10), (Y_MAX_POS - 10), 20 }

#elif MiniTreeMachine == 2  // i3
  #define CUSTOM_MACHINE_NAME "MiniTree i3"

  #define X_BED_SIZE 220
  #define Y_BED_SIZE 220
  #define Z_MAX_POS  220

  #define BED_MAXTEMP 90
#endif

// 如果需要增加关闭电源功能，注释掉这两行
#define PSU_CONTROL
#define PSU_NAME "Power Supply"
#define PS_ON_PIN 21  // 这里定义是D21，缺省是11，可以更改成12，21
#define PS_OFF_CONFIRM
#define PS_OFF_SOUND
#define AUTO_POWER_CONTROL // 启用这个会启用无操作自动关机
#define POWER_TIMEOUT 90 // 缺省是30秒自动关机，改成90秒

// 热敏选择 注意 MKS GEN_L系列只能用100K的热敏电阻
// 小树定制固件，修改热敏类型为11。测量温度会更精准。
#define TEMP_SENSOR_0 11
#define TEMP_SENSOR_BED 11

// 热敏最低温度
#define HEATER_0_MINTEMP   -5
#define BED_MINTEMP        -5

// 最高温度
#define HEATER_0_MAXTEMP 265  //小树定制固件 原装加热棒和热敏 最高耐热250度，所以设置成+HOTEND_OVERSHOOT=265

// huhuzhu use:
//#define PID_K1 0.75

#define PID_EDIT_MENU         // Add PID editing to the "Advanced Settings" menu. (~700 bytes of PROGMEM)     小树定制固件，在屏幕开启PID修改菜单
#define PID_AUTOTUNE_MENU     // Add PID auto-tuning to the "Advanced Settings" menu. (~250 bytes of PROGMEM)     小树定制固件，在屏幕开启PID AutoTuning功能

// 小树定制固件，开启热床pid
#define PIDTEMPBED

// huhuzhu use:
//#define PID_FUNCTIONAL_RANGE 15
//#define EXTRUDE_MINTEMP 100
//#define EXTRUDE_MAXLENGTH 1000

// 限位电位调整
#if defined(BLTOUCH) || defined(TOUCH_MI_PROBE)
  // 自动调平 by huhuzhu
  #define X_MIN_ENDSTOP_INVERTING true // Set to true to invert the logic of the endstop.
  #define Y_MIN_ENDSTOP_INVERTING true // Set to true to invert the logic of the endstop.
  #define Z_MIN_ENDSTOP_INVERTING false // Set to true to invert the logic of the endstop.
  #define X_MAX_ENDSTOP_INVERTING true // Set to true to invert the logic of the endstop.
  #define Y_MAX_ENDSTOP_INVERTING true // Set to true to invert the logic of the endstop.
  #define Z_MAX_ENDSTOP_INVERTING true // Set to true to invert the logic of the endstop.
  #define Z_MIN_PROBE_ENDSTOP_INVERTING false // Set to true to invert the logic of the probe.
#else
  // 不使用自动调平
  #define X_MIN_ENDSTOP_INVERTING true // Set to true to invert the logic of the endstop.
  #define Y_MIN_ENDSTOP_INVERTING true // Set to true to invert the logic of the endstop.
  #define Z_MIN_ENDSTOP_INVERTING true // Set to true to invert the logic of the endstop.
  #define X_MAX_ENDSTOP_INVERTING true // Set to true to invert the logic of the endstop.
  #define Y_MAX_ENDSTOP_INVERTING true // Set to true to invert the logic of the endstop.
  #define Z_MAX_ENDSTOP_INVERTING true // Set to true to invert the logic of the endstop.
  #define Z_MIN_PROBE_ENDSTOP_INVERTING true // Set to true to invert the logic of the probe.
#endif

// 缺省驱动是：A4988，选项是：TMC2208/TMC2209，2225驱动请填TMC2208
#define _DRIVER_TYPE A4988
//静音驱动开启Uart 普通模式请全部关闭
#define X_DRIVER_TYPE  _DRIVER_TYPE
#define Y_DRIVER_TYPE  _DRIVER_TYPE
#define Z_DRIVER_TYPE  _DRIVER_TYPE
#define Z2_DRIVER_TYPE _DRIVER_TYPE
#define E0_DRIVER_TYPE _DRIVER_TYPE

// 小树定制固件 触发式限位，可以降低cpu开销 开启uart自动关闭
#if _DRIVER_TYPE == A4988
  #define ENDSTOP_INTERRUPTS_FEATURE
#endif

// 小树定制固件 开启限位损坏检测
#define DETECT_BROKEN_ENDSTOP

// 小树定制固件，最高加速度，修改了挤出机的加速度，可以支持更高的回抽速度，用于改善拉丝
// XenoXue use:
//#define DEFAULT_MAX_ACCELERATION      { 3000, 3000, 50, 10000 }
// Tuba use:
#define DEFAULT_MAX_ACCELERATION      { 3000, 3000, 100, 10000 }
// huhuzhu use:
//#define DEFAULT_MAX_ACCELERATION      { 3000, 3000, 100, 5000 }

// 加速度 影响振纹 及回抽拉丝
// XenoXue use: 1000
// Tuba use:    2000
// huhuzhu use: 3000
#define DEFAULT_ACCELERATION          1000    // XYZE打印加速度
#define DEFAULT_RETRACT_ACCELERATION  2000    // E回抽加速度
#define DEFAULT_TRAVEL_ACCELERATION   2000    // XYZ空驶加速度

// 小树定制 抖动速度
//#define CLASSIC_JERK
#ifdef CLASSIC_JERK
  // XenoXue use: 5.0 5.0 0.3
  // huhuzhu use: 10.0 10.0 0.3
  // Tuba use: 10.0 10.0 0.3
  #define DEFAULT_XJERK 10.0
  #define DEFAULT_YJERK 10.0
  #define DEFAULT_ZJERK  0.3
#endif

// 曲线增强 路径转贝赛尔流畅度高 但需要占用算力，有群友反映直角转弯堆料
#define S_CURVE_ACCELERATION

// BLtouch/3DtouchPIN
#ifdef BLTOUCH
  // XenoXue: 默认为D11针脚
  //#define Z_MIN_PROBE_PIN 11
  // Tuba: 探针使用端口 X_MAX （2pin黑=负极GND 白=XMAX D2端口）
  #define Z_MIN_PROBE_PIN   2
  #define SERVO0_PIN       21  //舵机使用端口 （3pin 绿=负极 红=5V 橙=D21）
  #define GRID_MAX_POINTS_X 5  //调平探测点数量
#endif

#ifdef TOUCH_MI_PROBE
  #define TOUCH_MI_RETRACT_Z 0.7                // Height at which the probe retracts <探针收针时上升高度 自调 若收针失败 可以尝试增大该值>
  #define TOUCH_MI_DEPLOY_XPOS (X_MAX_BED + 6)  // For a magnet on the right side of the bed <磁铁放置位置 默认是X最大值+6的位置 可以修改 (不要放在原点！！！)>
  //#define TOUCH_MI_MANUAL_DEPLOY              // For manual deploy (LCD menu) <启用手动部署>
#endif

#if defined(BLTOUCH) || defined(TOUCH_MI_PROBE)
  #define USE_PROBE_FOR_Z_HOMING

  /**
   * 探针偏移调整 相对于喷头位置
   * 仅在探针启用时生效
   *
   * 例子(下图中的数字为下表中的例子):
   * Some examples:
   *   #define NOZZLE_TO_PROBE_OFFSET { 10, 10, -1 }   // Example "1"
   *   #define NOZZLE_TO_PROBE_OFFSET {-10,  5, -1 }   // Example "2"
   *   #define NOZZLE_TO_PROBE_OFFSET {  5, -5, -1 }   // Example "3"
   *   #define NOZZLE_TO_PROBE_OFFSET {-15,-10, -1 }   // Example "4"
   *
   *     +--  后方 --+
   *     |    [+]    |
   *     |        1  |  <-- 例如 "1" (右侧+,  后方+)
   *  左 |  2        | 右        "2" (左侧-,  后方+)
   *     |[-]  N  [+]|           "3" (右侧+,  前方-)
   *  侧 |       3   | 侧        "4" (左侧-,  前方-)
   *     | 4         |
   *     |    [-]    |
   *原点→O--  前方 --+
  */
  // Tuba use:
  #define NOZZLE_TO_PROBE_OFFSET { 43, 9, 0 } //探针偏移调整 相对于喷头位置
  // XenoXue use:
  //#define NOZZLE_TO_PROBE_OFFSET { -8, 3, -2.5 }

  #define XY_PROBE_FEEDRATE (80*60)// 调平时的速度 (133*60)

  #define AUTO_BED_LEVELING_BILINEAR //探针模式

  #define PROBING_MARGIN_LEFT PROBING_MARGIN
  #define PROBING_MARGIN_RIGHT PROBING_MARGIN
  #define PROBING_MARGIN_FRONT PROBING_MARGIN
  #define PROBING_MARGIN_BACK PROBING_MARGIN

#else
  // 禁止使用Z_min限位作为Z探针位置，如果使用自动调平需要禁用这个
  #define Z_MIN_PROBE_DISABLE
#endif

// 调平边界 <可以认为是热床边预留长度 防止探针超过床>
#define PROBING_MARGIN 50

// 电机方向修改 若电机方向错位 可通过修改布尔值实现 XYZE [TEATF2]
// XenoXue use: false false false false
// huhuzhu use: false false true true
#define INVERT_X_DIR true //false正 true反
#define INVERT_Y_DIR true
#define INVERT_Z_DIR false
#define INVERT_E0_DIR true

// 断料检测 默认关闭
#define FILAMENT_RUNOUT_SENSOR
// 缺省使用D4昨晚断料检测的脚位，这里使用ZMax作为检测脚位--CoreXY
#define FIL_RUNOUT_PIN       19
// 若失败 删除注释使用高电平
//#define FIL_RUNOUT_STATE     HIGH

// 小树定制固件 开启z安全归零设置，防止喷嘴刮花平台
#define Z_SAFE_HOMING

/**
 *  查看好设备的XYZ 下面是设备三视图ABCD点所对应位置
 *    Y                     Z                     Z
 *    ^     B-------C       ^     B-------C       ^     B-------C
 *    |    /       /        |    /       /        |    /       /
 *    |   /       /         |   /       /         |   /       /
 *    |  A-------D          |  A-------D          |  A-------D
 *    +-------------->X     +-------------->X     +-------------->Y
 *     XY_SKEW_FACTOR        XZ_SKEW_FACTOR        YZ_SKEW_FACTOR
 *
 * [床偏移更正]
 * 打印一个正方体 然后测量 A-C   B-D    A-D 的长度(mm) 输入到下面
 */
//#define SKEW_CORRECTION

// 可使用EEPROM保存
#define EEPROM_SETTINGS

// 小树定制固件 PLA
// XenoXue use: 200 60 35
// huhuzhu use: 190 70 35
#define PREHEAT_1_TEMP_HOTEND 200
#define PREHEAT_1_TEMP_BED     60
#define PREHEAT_1_TEMP_CHAMBER 35

// 探针停泊位置
#define NOZZLE_PARK_FEATURE

#define LCD_LANGUAGE zh_CN

#define SDSUPPORT

// 小树定制固件 开启单独归零菜单选项
#define INDIVIDUAL_AXIS_HOMING_MENU

#if DisplayScreen == 0
  // 小树定制固件 12864大屏
  #define REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER
#elif DisplayScreen == 1
  // 小树定制 12864小屏
  #define MKS_MINI_12864
#endif

// LED driving pin
#define NEOPIXEL_PIN     4


// Configuration_adv.h
//=======================

// 小树定制固件，主板风扇设置，可以只在电机移动的时候开启，电机都停止的时候关闭
//#define USE_CONTROLLER_FAN
//#define CONTROLLER_FAN_PIN 36 // must define a pin if USE_CONTROLLER_FAN

//常开风扇改可控 风扇接到E1加热棒端口 喷头50度以上启动 低于50度关闭 需要占用算力
#if 0
  #define FAN_MIN_PWM 50
  // 小树定制固件，挤出机风扇（常开风扇）。可以选择把常开风扇插到常开风扇上去，然后在喷嘴温度
  // 超过设定值的时候再开启常开风扇，这样可以降低待机噪音。GenL只有1个可控风扇位，所以无法使用
  #define E0_AUTO_FAN_PIN 7
#endif

#if MiniTreeMachine == 0  // Tx
  // 小树定制 Z电机数量
  #define NUM_Z_STEPPER_DRIVERS 1

#elif MiniTreeMachine == 1 // CoreXY
  // 小树定制 Z电机数量
  #define NUM_Z_STEPPER_DRIVERS 2
  //#define INVERT_Z2_VS_Z_DIR //小树定制 Z2电机反转方向 禁用 by cytown

#elif MiniTreeMachine == 2 // i3
  // 小树定制 Z电机数量
  #define NUM_Z_STEPPER_DRIVERS 2

#endif

// 显示打印机信息
#define LCD_INFO_MENU
//#define LCD_PRINTER_INFO_IS_BOOTSCREEN

// 小树定制固件，开机画面持续时间。默认4秒，改为1.5秒
#define BOOTSCREEN_TIMEOUT 1500      // (ms) Total Duration to display the boot screen(s)

// 紧凑显示坐标
#define LCD_DECIMAL_SMALL_XY

// 显示耗材消耗长度
#define LCD_SHOW_E_TOTAL

// 小树定制固件 sd卡改为只读模式，可以节省2k的flash空间。开启断电续打需要关闭这个功能。使用esp3D的上传文件功能也需要关闭这个选项
//#define SDCARD_READONLY                 // Read-only SD card (to save over 2K of flash)

// 小树定制固件 sd卡打印结束后，自动关闭电机。默认true改为false。 再切片的时候可以直接添加gcode达到一样的效果
#define SD_FINISHED_STEPPERRELEASE false  // Disable steppers when SD Print is finished

// 小树定制固件 默认情况下，机器启动后会自动执行sd卡中auto开头的g文件。开启这个选项，就可以关闭这个功能。以节省flash和内存
#define NO_SD_AUTOSTART                   // Remove auto#.g file support completely to save some Flash, SRAM

#define MEDIA_MENU_AT_TOP                 // Force the media menu to be listed on the top of the main menu 小树定制固件

// 小树定制固件，断电续打功能，使用sd卡打印的时候，会在sd卡创建一个临时文件，每打印一层都会在临时文件中添加一个标识。
// 断电重启后，检测到临时文件就会触发断电续打。这个功能是创想三维制作的。
#define POWER_LOSS_RECOVERY
// 小树定制固件，默认开启断电续打。可以通过M413 Sn 来修改。修改后可以用M500保存到eeprom来覆盖这个选项
#define PLR_ENABLED_DEFAULT   true  // Power Loss Recovery enabled by default. (Set with 'M413 Sn' & M500)    

// 显示打印进度百分比
#define DOGM_SD_PERCENT

// 长文件名自动滚动
#define SCROLL_LONG_FILENAMES

// 提高二进制文件传输效率
#define BINARY_FILE_TRANSFER

// 中英选择菜单，注释掉这些就只能使用中文了
// 小树定制固件 新增语言选择，可以选择在菜单里面直接选择英文
#define LCD_LANGUAGE_2 en
// 小树定制固件 更改语言后自动保存
#define LCD_LANGUAGE_AUTO_SAVE // Automatically save language to EEPROM on change

// 小树定制固件，开启微步调整，主要是打印过程中可以调整z轴，来达到调平的效果。
#define BABYSTEPPING

#if defined(BLTOUCH) || defined(TOUCH_MI_PROBE)
  #define BABYSTEP_ZPROBE_OFFSET // Combine M851 Z and Babystepping
#endif

//直线增强 控制直线速度突变流畅程度 远程机型开启 需要占用算力
//#define LIN_ADVANCE
#ifdef LIN_ADVANCE
  //上 https://marlinfw.org/ 官网生成测试图形打印选最优K值
  #define LIN_ADVANCE_K 2
  //小树定制固件，开启这个选项来兼容S-Curve  Enable this option to permit S-Curve Acceleration
  #define EXPERIMENTAL_SCURVE
#endif

#define PARK_HEAD_ON_PAUSE                    // Park the nozzle during pause and filament change.

// 小树定制固件，开启暂停移开喷头的高级功能  断料检测也需要开启此项
#define ADVANCED_PAUSE_FEATURE

// 这里注意，如果哪个驱动不是TMC2208/2209，就要注释掉哪个
#if _DRIVER_TYPE == TMC2208 || _DRIVER_TYPE == TMC2209
  #define X_CURRENT       650
  #define Y_CURRENT       650
  #define Z_CURRENT       700
  #define Z2_CURRENT      700
  #define E0_CURRENT      700
#endif

#undef DisplayScreen
#undef MiniTreeMachine

// Other functions
//=======================

#define MiniTreeFunc

//===========================================================================
//=======================固件测试阶段 有问题群里反映=========================
//===========================================================================
