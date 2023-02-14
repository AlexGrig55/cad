#pragma once

#include "../base/cad_obj.h"
#include "../table/layer.h"

#include <geom/geom.hpp>

namespace cad::entity
{
	class CAD_API BaseEntity : public base::Handler, public table::ILayerUser
	{
		types::String		_layer;
		types::String		_lineType;

		Color				_color;

		types::real			_lineTypeScale;

		enums::LineWeight	_lineWeight;

		bool				_visible;

	protected:
		BaseEntity(const BaseEntity& val) = default;
		BaseEntity(BaseEntity&& val) = default;
		BaseEntity& operator=(const BaseEntity& val) = default;

	public:
		constexpr BaseEntity(const Color& color = Color(enums::Color::ByLayer),
			const types::String& layer = "0", const types::String& lineType = "ByLayer")noexcept :
			_layer(layer), _lineType(lineType), _lineTypeScale(1), _color(color),
			_lineWeight(enums::LineWeight::ByLayer), _visible(true) {}

		virtual ~BaseEntity() = default;


#pragma region getters_setters
		constexpr const auto& lineType()				const noexcept { return _lineType; }
		constexpr void	setLineType(const types::String& val)	noexcept { _lineType = val; }

		constexpr auto	lineTypeScale()					const noexcept { return _lineTypeScale; }
		constexpr void	setLineTypeScale(float& val)	noexcept { _lineTypeScale = val; }

		constexpr const auto&	color()					const noexcept { return _color; }
		constexpr void	setColor(const Color& val)		noexcept { _color = val; }

		constexpr auto	lineWeight()					const noexcept { return _lineWeight; }
		constexpr void	setLineWeight(enums::LineWeight val)noexcept { _lineWeight = val; }

		constexpr auto	visible()						const noexcept { return _visible; }
		constexpr void	setVisible(bool val)			noexcept { _visible = val; }
#pragma endregion getters_setters


#pragma region actions
		BaseEntity* move(const geom::Vector3& normal, float length)noexcept {
			assert(normal.isNormal()); return move(normal * length);
		}
		BaseEntity* move(const geom::Vector2& direction)noexcept {
			return move(direction.toVector3());
		}
		BaseEntity* move(const geom::Vector2& normal, float length)noexcept {
			return move(normal.toVector3(),length);
		}

		BaseEntity* rotate(const geom::Point2_d& center, geom::Angle ang)noexcept{
			return rotate({ center.x(),center.y(),0 }, { 0,0,1 }, ang);
		}

		BaseEntity* scale(const geom::Point3_d& center, float scale)noexcept {
			return this->scale(center, geom::Vector3(scale));
		}
		BaseEntity* scale(const geom::Point2_d& center, const geom::Vector2& scale)noexcept {
			return this->scale({ center.x(),center.y(),0 }, { scale.x(),scale.y(),1 });
		}
		BaseEntity* scale(const geom::Point2_d& center, float scale)noexcept {
			return this->scale({ center.x(),center.y(),0 }, geom::Vector3(scale, scale,1));
		}

		BaseEntity* mirror(const geom::InfLine2_d& relativeLine)noexcept {
			geom::Vector3 n = relativeLine.normal().normal().toVector3();
			return mirror(geom::Plane_d({ relativeLine.pos().x(),relativeLine.pos().y(),0 },n));
		}
#pragma endregion actions


#pragma region virtual
		virtual constexpr enums::EntyType type() const noexcept = 0;
		virtual std::array<geom::Point3_d, 2> minMax() const noexcept = 0;
		virtual constexpr BaseEntity* copy() const = 0;


		virtual BaseEntity* move(const geom::Vector3& direct)noexcept = 0;
		virtual BaseEntity* rotate(const geom::Point3_d& center, const geom::Vector3& axis,
			geom::Angle ang)noexcept = 0;
		virtual BaseEntity* scale(const geom::Point3_d& center,const geom::Vector3& scale)noexcept = 0;
		virtual BaseEntity* mirror(const geom::Plane_d& relativePlane)noexcept = 0;
#pragma endregion virtual


#pragma region overrides
		constexpr const types::String& layer()					const noexcept override{ return _layer; }
		constexpr void setLayer(const types::String& name)		noexcept override { _layer = name; }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& reader) noexcept override;
#pragma endregion overrides
	};
}
