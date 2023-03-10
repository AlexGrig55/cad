#pragma once
#include "./table_record.h"


namespace cad::table
{
	class IViewUser :public base::IUser
	{
	public:
		virtual constexpr ~IViewUser() noexcept = default;
		virtual constexpr const types::String& view()const noexcept = 0;
		virtual void setView(const types::String& name)noexcept = 0;
	};

	class CAD_API View : public TableRecord< IViewUser>
	{
	public:
		enum class RenderMode :types::int16
		{
			Classic2D, Wireframe, HiddenLine, FlatShaded, GouraudShaded,
			FlatShadedWireframe, GroudShadedWireframe
		};
		enum class OrthoType :types::int16
		{
			No = 0, Top = 1, Bot = 2, Front = 3, Back = 4, Left = 5, Right = 6
		};

	private:
		types::Point2	_center;//10,20
		types::Point3	_directionFromTarget={0,0,1};//11, 21, 31
		types::Point3	_targetPoint;//12, 22, 32
		types::Point3	_ucsOrigin;//110, 120, 130
		types::Point3	_ucsXAxis;//111, 121, 131
		types::Point3	_ucsYAxis;//112, 122, 132

		types::real		_viewHeight = 100;//40
		types::real		_viewWidth = 200;//41
		types::real		_lensLength = 50;//42
		types::real		_frontClippingPlane = 0;//43
		types::real		_backClippingPlane = 0;//44
		types::real		_twistAngle = 0;//50
		types::real		_ucsElevation = 0;//146

		types::int16	_viewMode=16;//71
		RenderMode		_renderMode = RenderMode::Classic2D;//281
		types::int16	_ucsAssociated = 1;//72
		types::int16	_isCameraPlottable = 0;//73
		OrthoType		_ucsOrthoType = OrthoType::No;//79

	public:
		constexpr View(const types::String& name)noexcept:TableRecord(name){}
		constexpr ~View()noexcept = default;

#pragma region getters_setters
		constexpr auto& center()const noexcept { return _center; }
		constexpr void setCenter(const types::Point2& val) noexcept { _center = val; }

		constexpr auto& directionFromTarget()const noexcept { return _directionFromTarget; }
		constexpr void setDirectionFromTarget(const types::Point3& val) noexcept { _directionFromTarget = val; }

		constexpr auto& targetPoint()const noexcept { return _targetPoint; }
		constexpr void setTargetPoint(const types::Point3& val) noexcept { _targetPoint = val; }

		constexpr auto& ucsOrigin()const noexcept { return _ucsOrigin; }
		constexpr void setUcsOrigin(const types::Point3& val) noexcept { _ucsOrigin = val; }

		constexpr auto& ucsXAxis()const noexcept { return _ucsXAxis; }
		constexpr void setUcsXAxis(const types::Point3& val) noexcept { _ucsXAxis = val; }

		constexpr auto& ucsYAxis()const noexcept { return _ucsYAxis; }
		constexpr void setUcsYAxis(const types::Point3& val) noexcept { _ucsYAxis = val; }

		constexpr auto viewHeight()const noexcept { return _viewHeight; }
		constexpr void setViewHeight(types::real val) noexcept { _viewHeight = val; }

		constexpr auto viewWidth()const noexcept { return _viewWidth; }
		constexpr void setViewWidth(types::real val) noexcept { _viewWidth = val; }

		constexpr auto lensLength()const noexcept { return _lensLength; }
		constexpr void setLensLength(types::real val) noexcept { _lensLength = val; }

		constexpr auto frontClippingPlane()const noexcept { return _frontClippingPlane; }
		constexpr void setFrontClippingPlane(types::real val) noexcept { _frontClippingPlane = val; }

		constexpr auto backClippingPlane()const noexcept { return _backClippingPlane; }
		constexpr void setBackClippingPlane(types::real val) noexcept { _backClippingPlane = val; }

		constexpr auto twistAngle()const noexcept { return _twistAngle; }
		constexpr void setTwistAngle(types::real val) noexcept { _twistAngle = val; }

		constexpr auto ucsElevation()const noexcept { return _ucsElevation; }
		constexpr void setUcsElevation(types::real val) noexcept { _ucsElevation = val; }

		constexpr auto viewMode()const noexcept { return _viewMode; }
		constexpr void setViewMode(types::int16 val) noexcept { _viewMode = val; }

		constexpr auto renderMode()const noexcept { return _renderMode; }
		constexpr void setRenderMode(RenderMode val) noexcept { _renderMode = val; }

		constexpr auto ucsAssociated()const noexcept { return _ucsAssociated; }
		constexpr void setUcsAssociated(types::int16 val) noexcept { _ucsAssociated = val; }

		constexpr auto isCameraPlottable()const noexcept { return (bool)_isCameraPlottable; }
		constexpr void setIsCameraPlottable(bool val) noexcept { _isCameraPlottable = val; }

		constexpr auto ucsOrthoType()const noexcept { return _ucsOrthoType; }
		constexpr void setUcsOrthoType(OrthoType val) noexcept { _ucsOrthoType = val; }
#pragma endregion getters_setters


#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "VIEW"; }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader, char auxilData = -1) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer, char auxilData = -1) noexcept override;
#pragma endregion overrides
	};
}
