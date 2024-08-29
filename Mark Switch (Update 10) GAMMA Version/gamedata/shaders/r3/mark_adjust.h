#define MARK_ADJUST 1

uniform float4 markswitch_current;
uniform float4 markswitch_count;
uniform float4 markswitch_color;

int mark_sides()
{
	int sides = 1;
	while (sides * sides < int(markswitch_count.x))
	{
		sides += 1;
	}
	
	return sides;
}

float2 mark_adjust(float2 pos)
{
	int sides = mark_sides();
	
	float d_x = int(markswitch_current.x) % sides;
	float d_y = int(markswitch_current.x) / sides;
	
	float p_x = clamp(d_x + pos.x, d_x, d_x + 1) / sides;
	float p_y = clamp(d_y + pos.y, d_y, d_y + 1) / sides;
	
	return float2(p_x, p_y);
}

float current_lum()
{
	float lum_min = 0.85;
	float lum_max = 3;
	float lum = s_tonemap.Load(int3(0, 0, 0)).x;
	return clamp(1 - (lum - lum_min) / (lum_max - lum_min), 0, 1);
}

float4 lum_adjust(float4 color)
{
	if (markswitch_color.a)
		color = float4(markswitch_color.r, markswitch_color.g, markswitch_color.b, markswitch_color.a * (color.r + (1 - current_lum()) * color.g));
	return color;
}
