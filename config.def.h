/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 0;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "SauceCodePro Nerd Font:size=20" };
static const char dmenufont[]       = "SauceCodePro Nerd Font:size=20";
static const char col1[]       = "#000000";
static const char col2[]       = "#000000";
static const char col3[]       = "#ffffff";
static const char col4[]       = "#03A9F4";
static const char col5[]       = "#ffff00";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col3, col1, col2 },
	[SchemeSel]  = { col4, col5,  col5  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance           title          	tags mask     isfloating   monitor    float x,y,w,h         floatborderpx*/
	{ "Gimp",       NULL,              NULL,          	0,            1,           -1,        50,50,500,500,        5 },
	{ "Firefox",    NULL,              NULL,          	1 << 8,       0,           -1,        50,50,500,500,        5 },
  { "Alacritty",  "ttyclock",        "Clock",       	0,            1,           -1,        0,0,1376,625,         -1 },
  { "Alacritty",  "projectselectorcode", "Projects",	0,            1,           -1,        0,0,800,625,         -1 },
  { "Alacritty",  "projectselectornvim", "Projects",	0,            0,           -1,        0,0,800,625,         -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
};

/* key definitions */
#define SUPER Mod4Mask
#define SHIFT ShiftMask
#define CONTROL ControlMask

#define TAGKEYS(KEY,TAG) \
	{ SUPER,                   KEY,      view,           {.ui = 1 << TAG} }, \
	{ SUPER|CONTROL,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ SUPER|SHIFT,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ SUPER|CONTROL|SHIFT,     KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run_i" };
static const char *termcmd[]  = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key                function              argument */
	{ SUPER,                       XK_Delete,         killunsel,            {.i = 1} },
	{ SUPER,                       XK_Return,         spawn,                {.v = termcmd } },
	{ SUPER,                       XK_Tab,            view,                 {0} },
	{ SUPER,                       XK_a,              spawn,                SHCMD("alacritty -e ssh -i ~/Documents/carmeter_aws_keypair_11062017.pem ubuntu@car-meter.com") },
	{ SUPER,                       XK_b,              spawn,                SHCMD("google-chrome-stable --enable-features=WebUIDarkMode --force-dark-mode --force-device-scale-factor=1.2") },
	{ SUPER,                       XK_c,              spawn,                SHCMD("alacritty -t 'Clock' --class 'ttyclock' -e /usr/local/bin/clock") },
	{ SUPER,                       XK_f,              setlayout,            {.v = &layouts[1]} },
	{ SUPER,                       XK_h,              shiftviewclients,     {.i = -1 } },
	{ SUPER,                       XK_i,              shiftview,            {.i = +1 } },
	{ SUPER,                       XK_j,              focusstack,           {.i = +1 } },
	{ SUPER,                       XK_k,              focusstack,           {.i = -1 } },
	{ SUPER,                       XK_l,              shiftviewclients,     {.i = +1 } },
	{ SUPER,                       XK_m,              togglemonocle,        {NULL} },
	{ SUPER,                       XK_n,              spawn,                SHCMD("alacritty -e nvim") },
	{ SUPER,                       XK_o,              spawn,                SHCMD("alacritty -e htop") },
	{ SUPER,                       XK_p,              spawn,                SHCMD("clipmenu && xdotool key shift+Insert") },
	{ SUPER,                       XK_r,              spawn,                {.v = dmenucmd } },
	{ SUPER,                       XK_space,          view,                 {.ui = ~0 } },
	{ SUPER,                       XK_t,              setlayout,            {.v = &layouts[0]} },
	{ SUPER,                       XK_u,              shiftview,            {.i = -1 } },
	{ SUPER,                       XK_v,              setlayout,            {.v = &layouts[3]} },
	{ SUPER,                       XK_w,              spawn,                SHCMD("alacritty -t 'Projects' --class 'projectselectorcode' -e /usr/local/bin/projectselectorcode") },

	{ SUPER,                       XK_x,              killclient,           {0} },
	{ SUPER,                       XK_z,              spawn,                SHCMD("alacritty -t \"vifm\" -e vifmrun") },
	{ SUPER|SHIFT,                 XK_0,              tag,                  {.ui = ~0 } },
	{ SUPER|SHIFT,                 XK_F1,             spawn,                SHCMD("sudo reboot") },
	{ SUPER|SHIFT,                 XK_F2,             spawn,                SHCMD("sudo poweroff") },
	{ SUPER|SHIFT,                 XK_h,              tagtoleft,            {.i = -1 } },
	{ SUPER|SHIFT,                 XK_x,              killunsel,            {0} },
  { SUPER|SHIFT,                 XK_BackSpace,      spawn,                SHCMD("slimlock") },
  { SUPER|SHIFT,                 XK_Return,         winview,              {0} },
  { SUPER|SHIFT,                 XK_j,              pushdown,             {0} },
  { SUPER|SHIFT,                 XK_k,              pushup,               {0} },
  { SUPER|SHIFT,                 XK_l,              tagtoright,           {.i = +1 } },
  { SUPER|SHIFT,                 XK_n,              spawn,                SHCMD("alacritty -e neomutt") },
  { SUPER|SHIFT,                 XK_p,              spawn,                SHCMD("clipmenu") },
  { SUPER|SHIFT,                 XK_q,              quit,                 {0} },
  { SUPER|SHIFT,                 XK_r,              quit,                 {1} },
	{ SUPER|SHIFT,                 XK_w,              spawn,                SHCMD("alacritty -t 'Projects' --class 'projectselectornvim' -e /usr/local/bin/projectselectornvim") },
	TAGKEYS(                       XK_1,              0)
	TAGKEYS(                       XK_2,              1)
	TAGKEYS(                       XK_3,              2)
	TAGKEYS(                       XK_4,              3)
	TAGKEYS(                       XK_5,              4)
	TAGKEYS(                       XK_6,              5)
	TAGKEYS(                       XK_7,              6)
	TAGKEYS(                       XK_8,              7)
	TAGKEYS(                       XK_9,              8)
};

