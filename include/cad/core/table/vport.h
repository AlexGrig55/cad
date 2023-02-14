#pragma once
#include "./table_object.h"


namespace cad::table
{
	class CAD_API Vport : public TableObject
	{
	public:
		enum class RenderMode :types::int16
		{
			Classic2D, Wireframe, HiddenLine, FlatShaded, GouraudShaded,
			FlatShadedWireframe, GroudShadedWireframe
		};
		enum class UcsOrthoType :types::int16
		{
			NotOrtho, Top, Bot, Front, Back, Left, Right
		};

	private:
		types::String	_plotStyleSheet;//1
		types::Point2	_loverLelftCorner;//10,20
		types::Point2	_upperRightCorner;//11,21
		types::Point2	_center;//12,22
		types::Point2	_snapBasePoint;//13,23
		types::Point2	_snapSpacing;//14,24
		types::Point2	_gridSpacing;//15,25
		types::Point3	_directionFromTargetPoint;//16,26,36
		types::Point3	_viewTargetPoint;//17,27,37

		types::Point3	_ucsOrigin;//110,120,130
		types::Point3	_ucsXaxis;//111,121,131
		types::Point3	_ucsYaxis;//112,122,132

		types::real		_lensLength=50;//42
		types::real		_frontClippingPlane=0;//43
		types::real		_backClippingPlane=0;//44
		types::real		_viewHeight=100;//40
		types::real		_aspectRatio = 2;//41
		types::real		_snapRotation=0;//50
		types::real		_viewTwistAngle=0;//51
		types::real		_elevation=0;//146
		types::real		_brightness=0;//141
		types::real		_contrast=0;//142

		types::int16	_circleSides=2000;//72
		RenderMode		_renderMode= RenderMode::Classic2D;//281
		types::int16	_viewMode=16;//71
		types::int16	_ucsIconSetting=3;//74
		UcsOrthoType	_ucsOrthoType= UcsOrthoType::NotOrtho;//79
		types::int16	_shadePlotSetting=0;//170
		types::int16	_majorGridLines=3;//60
		types::boolean	_defaultLightOn=1;//292
		types::int16	_defaultLightType=0;//282

		types::int16	_ambientColor[3]{ (types::int16)250,(types::int16)3355443 ,(types::int16)0};//63, 421, 431

	public:
		constexpr Vport(const types::String& name)noexcept:TableObject(name){}


#pragma region getters_setters
		constexpr auto plotStyleSheet()const noexcept { return _plotStyleSheet; }
		constexpr void setPlotStyleSheet(const types::String& val) noexcept { _plotStyleSheet =val; }

		constexpr auto loverLelftCorner()const noexcept { return _loverLelftCorner; }
		constexpr void setLoverLelftCorner(const types::Point2& val) noexcept { _loverLelftCorner = val; }

		constexpr auto upperRightCorner()const noexcept { return _upperRightCorner; }
		constexpr void setUpperRightCorner(const types::Point2& val) noexcept { _upperRightCorner = val; }

		constexpr auto center()const noexcept { return _center; }
		constexpr void setCenter(const types::Point2& val) noexcept { _center = val; }

		constexpr auto snapBasePoint()const noexcept { return _snapBasePoint; }
		constexpr void setSnapBasePoint(const types::Point2& val) noexcept { _snapBasePoint = val; }

		constexpr auto snapSpacing()const noexcept { return _snapSpacing; }
		constexpr void setSnapSpacing(const types::Point2& val) noexcept { _snapSpacing = val; }

		constexpr auto gridSpacing()const noexcept { return _gridSpacing; }
		constexpr void setGridSpacing(const types::Point2& val) noexcept { _gridSpacing = val; }

		constexpr auto directionFromTargetPoint()const noexcept { return _directionFromTargetPoint; }
		constexpr void setDirectionFromTargetPoint(const types::Point3& val) noexcept { _directionFromTargetPoint = val; }

		constexpr auto viewTargetPoint()const noexcept { return _viewTargetPoint; }
		constexpr void setViewTargetPoint(const types::Point3& val) noexcept { _viewTargetPoint = val; }

		constexpr auto ucsOrigin()const noexcept { return _ucsOrigin; }
		constexpr void setUcsOrigin(const types::Point3& val) noexcept { _ucsOrigin = val; }

		constexpr auto ucsXaxis()const noexcept { return _ucsXaxis; }
		constexpr void setUcsXaxis(const types::Point3& val) noexcept { _ucsXaxis = val; }

		constexpr auto ucsYaxis()const noexcept { return _ucsYaxis; }
		constexpr void setUcsYaxis(const types::Point3& val) noexcept { _ucsYaxis = val; }

		constexpr auto lensLength()const noexcept { return _lensLength; }
		constexpr void setLensLength(types::real val) noexcept { _lensLength = val; }

		constexpr auto frontClippingPlane()const noexcept { return _frontClippingPlane; }
		constexpr void setFrontClippingPlane(types::real val) noexcept { _frontClippingPlane = val; }

		constexpr auto backClippingPlane()const noexcept { return _backClippingPlane; }
		constexpr void setBackClippingPlane(types::real val) noexcept { _backClippingPlane = val; }

		constexpr auto viewHeight()const noexcept { return _viewHeight; }
		constexpr void setViewHeight(types::real val) noexcept { _viewHeight = val; }

		constexpr auto aspectRatio()const noexcept { return _aspectRatio; }
		constexpr void setAspectRatio(types::real val) noexcept { _aspectRatio = val; }

		constexpr auto snapRotation()const noexcept { return _snapRotation; }
		constexpr void setSnapRotation(types::real val) noexcept { _snapRotation = val; }

		constexpr auto viewTwistAngle()const noexcept { return _viewTwistAngle; }
		constexpr void setViewTwistAngle(types::real val) noexcept { _viewTwistAngle = val; }

		constexpr auto elevation()const noexcept { return _elevation; }
		constexpr void setElevation(types::real val) noexcept { _elevation = val; }

		constexpr auto brightness()const noexcept { return _brightness; }
		constexpr void setBrightness(types::real val) noexcept { _brightness = val; }

		constexpr auto contrast()const noexcept { return _contrast; }
		constexpr void setContrast(types::real val) noexcept { _contrast = val; }

		constexpr auto circleSides()const noexcept { return _circleSides; }
		constexpr void setCircleSides(types::int16 val) noexcept { _circleSides = val; }

		constexpr auto renderMode()const noexcept { return _renderMode; }
		constexpr void setRenderMode(RenderMode val) noexcept { _renderMode = val; }

		constexpr auto viewMode()const noexcept { return _viewMode; }
		constexpr void setViewMode(types::int16 val) noexcept { _viewMode = val; }

		constexpr auto ucsIconSetting()const noexcept { return _ucsIconSetting; }
		constexpr void setUcsIconSetting(types::int16 val) noexcept { _ucsIconSetting = val; }

		constexpr auto ucsOrthoType()const noexcept { return _ucsOrthoType; }
		constexpr void setUcsOrthoType(UcsOrthoType val) noexcept { _ucsOrthoType = val; }

		constexpr auto shadePlotSetting()const noexcept { return _shadePlotSetting; }
		constexpr void setShadePlotSetting(types::int16 val) noexcept { _shadePlotSetting = val; }

		constexpr auto majorGridLines()const noexcept { return _majorGridLines; }
		constexpr void setMajorGridLines(types::int16 val) noexcept { _majorGridLines = val; }

		constexpr auto defaultLightOn()const noexcept { return _defaultLightOn; }
		constexpr void setDefaultLightOn(types::int16 val) noexcept { _defaultLightOn = val; }

		constexpr auto defaultLightType()const noexcept { return _defaultLightType; }
		constexpr void setDefaultLightType(types::int16 val) noexcept { _defaultLightType = val; }

		//index < 3
		constexpr auto ambientColor(uint8_t i)const noexcept { assert(i<3); return _ambientColor[i]; }
		//index < 3
		constexpr void setAmbientColor(uint8_t i,types::int16 val) noexcept { assert(i < 3); _ambientColor[i] = val; }
#pragma endregion getters_setters


#pragma region overrides
		constexpr const char* dxfName() const noexcept { return "VPORT"; }

	protected:
		cad::Error::Code readDXF(translator::DXFInput& reader) noexcept override;
		cad::Error::Code writeDXF(translator::DXFOutput& writer) noexcept override;
#pragma endregion overrides
	};
}
