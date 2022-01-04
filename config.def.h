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
static const char col5[]       = "#03A9F4";
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
  /* class        instance           			title          	tags mask     isfloating   monitor    float x,y,w,h         floatborderpx*/
  { "Firefox",    NULL,              			NULL,          	1 << 8,       0,           -1,        50,50,500,500,        5 },
  { "Alacritty",  "ttyclock",       			"Clock",       	0,            1,           -1,        0,0,1000,563,         -1 },
  { "Alacritty",  "fzfcode",       			  "FZFCODE",      0,            1,           -1,        0,0,1500,1010,         1 },
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
	{ "###",      gaplessgrid },
};

/* key definitions */
#define ALT     Mod1Mask
#define CONTROL ControlMask
#define SHIFT   ShiftMask
#define SUPER   Mod4Mask

#define TAGKEYS(KEY,TAG) \
  { SUPER,                   KEY,      view,           {.ui = 1 << TAG} }, \
  { SUPER|CONTROL,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { SUPER|SHIFT,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { SUPER|CONTROL|SHIFT,     KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-nb", "#000000", "-nf", "#ffffff", "-sb", "#34a1eb", "-sf", "#000000", "-fn", dmenufont };
static const char *termcmd[]  = { "alacritty", NULL };

static Key keys[] = {
  /* modifier                    key                function              argument */
  { CONTROL|ALT,                 XK_1,              gridfocus,            {.ui = 1 } },
  { CONTROL|ALT,                 XK_2,              gridfocus,            {.ui = 2 } },
  { CONTROL|ALT,                 XK_3,              gridfocus,            {.ui = 3 } },
  { CONTROL|ALT,                 XK_4,              gridfocus,            {.ui = 4 } },
  { CONTROL|ALT,                 XK_5,              gridfocus,            {.ui = 5 } },
  { CONTROL|ALT,                 XK_6,              gridfocus,            {.ui = 6 } },
  { CONTROL|ALT,                 XK_7,              gridfocus,            {.ui = 7 } },
  { CONTROL|ALT,                 XK_8,              gridfocus,            {.ui = 8 } },
  { CONTROL|ALT,                 XK_9,              gridfocus,            {.ui = 9 } },
  { CONTROL|ALT,                 XK_0,              gridfocus,            {.ui = 10 } },

  { CONTROL|SHIFT,               XK_h,              spawn,                SHCMD("dunstctl history-pop") },
  { CONTROL|SHIFT,               XK_i,              spawn,                SHCMD("dunstctl close-all") },

  { SUPER,                       XK_Return,         spawn,                {.v = termcmd } },
  { SUPER,                       XK_Tab,            view,                 {0} },
  { SUPER,                       XK_a,              spawn,                SHCMD("alacritty -e ssh -i ~/Documents/carmeter_aws_keypair_11062017.pem ubuntu@car-meter.com") },
  { SUPER,                       XK_b,              spawn,                SHCMD("google-chrome-stable --enable-features=WebUIDarkMode --force-dark-mode --force-device-scale-factor=1.2") },
  { SUPER,                       XK_c,              spawn,                SHCMD("alacritty -t 'Clock' --class 'ttyclock' -e /usr/local/bin/clock") },
  { SUPER,                       XK_f,              togglefloating,       {NULL} },
	{ SUPER,                       XK_g,              setlayout,            {.v = &layouts[4]} },
  { SUPER,                       XK_h,              gridortagmovement,    {.i = -1 } },
  { SUPER,                       XK_i,              shiftview,            {.i = +1 } },
  { SUPER,                       XK_j,              focusstack,           {.i = +1 } },
  { SUPER,                       XK_k,              focusstack,           {.i = -1 } },
  { SUPER,                       XK_l,              gridortagmovement,    {.i = +1 } },
  { SUPER,                       XK_m,              togglemonocle,        {NULL} },
  { SUPER,                       XK_n,              spawn,                SHCMD("alacritty -e nvim") },
  { SUPER,                       XK_o,              spawn,                SHCMD("alacritty -e htop") },
  { SUPER,                       XK_p,              spawn,                SHCMD("clipmenu && xdotool key shift+Insert") },
  { SUPER,                       XK_r,              spawn,                {.v = dmenucmd } },
  { SUPER,                       XK_space,          togglewinview,        {0} },
  { SUPER,                       XK_t,              setlayout,            {.v = &layouts[2]} },
  { SUPER,                       XK_u,              shiftview,            {.i = -1 } },
  { SUPER,                       XK_v,              setlayout,            {.v = &layouts[3]} },
  { SUPER,                       XK_w,              spawn,                SHCMD("projectselectorcode") },
  { SUPER,                       XK_x,              killclient,           {0} },
  { SUPER,                       XK_z,              spawn,                SHCMD("alacritty -t \"vifm\" -e vifm +only") },

  { SUPER|SHIFT,                 XK_0,              tag,                  {.ui = ~0 } },
  { SUPER|SHIFT,                 XK_BackSpace,      spawn,                SHCMD("slimlock") },
  { SUPER|SHIFT,                 XK_F1,             spawn,                SHCMD("sudo reboot") },
  { SUPER|SHIFT,                 XK_F2,             spawn,                SHCMD("sudo poweroff") },
  { SUPER|SHIFT,                 XK_c,              spawn,                SHCMD("configselectornvim") },
  { SUPER|SHIFT,                 XK_e,              spawn,                SHCMD("projectselectorcode") },
  { SUPER|SHIFT,  					     XK_g,              togglegridmode,       {NULL}},
  { SUPER|SHIFT,                 XK_h,              tagtoleft,            {.i = -1 } },
  { SUPER|SHIFT,                 XK_i,              focusmaster,          {0} },
  { SUPER|SHIFT,                 XK_j,              pushdown,             {0} },
  { SUPER|SHIFT,                 XK_k,              pushup,               {0} },
  { SUPER|SHIFT,                 XK_l,              tagtoright,           {.i = +1 } },
  { SUPER|SHIFT,                 XK_m,              zoom,                 {0} },
  { SUPER|SHIFT,                 XK_n,              spawn,                SHCMD("alacritty -e neomutt") },
  { SUPER|SHIFT,                 XK_o,              spawn,                SHCMD("projectselectornvim") },
  { SUPER|SHIFT,                 XK_p,              spawn,                SHCMD("clipmenu") },
  { SUPER|SHIFT,                 XK_q,              quit,                 {0} },
  { SUPER|SHIFT,                 XK_r,              quit,                 {1} },
  { SUPER|SHIFT,                 XK_w,              spawn,                SHCMD("updatelastproject") },
  { SUPER|SHIFT,                 XK_x,              killall,              {0} },
  { SUPER|SHIFT,                 XK_z,              spawn,                SHCMD("alacritty -e vifm +only $(cat /tmp/lastdir)") },

  { SUPER|CONTROL,					     XK_h,              moveresize,		        {.v = (int []){ -25, 0, 0, 0 }}},
  { SUPER|CONTROL,					     XK_j,              moveresize,		        {.v = (int []){ 0, 25, 0, 0 }}},
  { SUPER|CONTROL,					     XK_k,              moveresize,		        {.v = (int []){ 0, -25, 0, 0 }}},
  { SUPER|CONTROL,					     XK_l,	            moveresize,		        {.v = (int []){ 25, 0, 0, 0 }}},

  { SUPER|CONTROL|ALT,			     XK_h,  	          moveresize,		        {.v = (int []){ 0, 0, -25, 0 }}},
  { SUPER|CONTROL|ALT,			     XK_j,  	          moveresize,		        {.v = (int []){ 0, 0, 0, 25 }}},
  { SUPER|CONTROL|ALT,			     XK_k,		          moveresize,		        {.v = (int []){ 0, 0, 0, -25 }}},
  { SUPER|CONTROL|ALT,			     XK_l,    	        moveresize,		        {.v = (int []){ 0, 0, 25, 0 }}},

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
