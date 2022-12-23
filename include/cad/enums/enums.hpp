#pragma once

namespace cad::enums
{
	enum class Version
	{
		VR12,
		V2000,
		V2004,
		V2007,
		V2010,
		V2013,
		V2018,
		Unknown
	};

	enum class Color
	{
		ByLayer,
		ByBlock,

		Red,
		Yellow,
		Green,
		Cyan,
		Blue,
		Magenta,
		White
	};

	enum class PointStyle
	{
		Dot,
		Void,
		Cross,
		RotatedCross,
		Line,

		Dot_Circle,
		Void_Circle,
		Cross_Circle,
		RotatedCross_Circle,
		Line_Circle,

		Dot_Square,
		Void_Square,
		Cross_Square,
		RotatedCross_Square,
		Line_Square,

		Dot_Square_Circle,
		Void_Square_Circle,
		Cross_Square_Circle,
		RotatedCross_Square_Circle,
		Line_Square_Circle
	};

	enum class EntyType
	{
		_3DFace,
		_3DSolid,
		Arc,
		Attdef,
		Attrib,
		Body,
		Circle,
		Dimension,
		Ellipse,
		Hatch,
		Helix,
		Image,
		Insert,
		Leader,
		Line,
		Polyline2D,
		Polyline3D,
		Mesh,
		Mline,
		MleaderStyle,
		Mleader,
		Mtext,
		PolyfaceMesh,
		Ray,
		Region,
		Shape,
		Solid,
		Spline,
		Surface,
		Table,
		Text,
		Trace,
		Viewport,
		Xline
	};
}