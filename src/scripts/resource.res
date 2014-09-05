Font default_font 
{ 
	filename=font.fnt
}

Target HUD
{
	size=256,256
	zbuffer=false
	resgroup=1
}



Sprite
{
	texture=characters
	rect=0,0,32,32
	hotspot
	blendmode=COLORMUL,ALPHABLEND,NOZWRITE
	color
	zorder
	flip
	resgroup=1

}

Animation hero.walk
{
	texture = cahraarecterst
	rect=0,128,32,32
}

test->SetColor(0xAAA00000)

Texture wall
{
	filename=data\cell_wall.jpg
	resgroup=1
}

Texture way
{
	filename=data\cell_wall.jpg
	resgroup=1
}

Texture button_1
{
	filename=data\button_1.png
	resgroup=1
}

Texture button_2
{
	filename=data\button_2.png
	resgroup=1
}
Texture button_3
{
	filename=data\button_3.png
	resgroup=1
}
Texture button_4
{
	filename=data\button_4.png
	resgroup=1
}
Texture button_5
{
	filename=data\button_5.png
	resgroup=1
}
Texture button_6
{
	filename=data\button_6.png
	resgroup=1
}

Texture button_7
{
	filename=data\button_7.png
	resgroup=1
}
Texture button_8
{
	filename=data\button_8.png
	resgroup=1
}
Texture button_9
{
	filename=data\button_9.png
	resgroup=1
}