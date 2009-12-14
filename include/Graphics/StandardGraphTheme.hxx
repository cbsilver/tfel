/*!
 * \file   StandardGraphTheme.hxx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   13 jan 2008
 */

#ifndef _LIB_TFEL_STANDARDGRAPHTHEME_HXX_
#define _LIB_TFEL_STANDARDGRAPHTHEME_HXX_ 

#include <cairomm/context.h>

#include"Graphics/Curve.hxx"
#include"Graphics/GraphLayout.hxx"
#include"Graphics/GraphTheme.hxx"

namespace tfel{

  namespace graphics
  {

    struct StandardGraphTheme
      : public GraphTheme
    {
      virtual void getDefaultColor(Curve::Color&,const unsigned short) const;
      virtual unsigned short getYTicsWidth(Cairo::RefPtr<Cairo::Context>&,
					   const std::map<double,std::string>&) const;
      virtual unsigned short getY2TicsWidth(Cairo::RefPtr<Cairo::Context>&,
	      				  const std::map<double,std::string>&) const;
      virtual unsigned short getXTicsHeight(Cairo::RefPtr<Cairo::Context>&,
	      				  const std::map<double,std::string>&) const;
      virtual unsigned short getX2TicsHeight(Cairo::RefPtr<Cairo::Context>&,
	      				   const std::map<double,std::string>&) const;
      virtual unsigned short getLeftMargin(void) const;
      virtual unsigned short getRightMargin(void) const;
      virtual unsigned short getUpperMargin(void) const;
      virtual unsigned short getDownMargin(void) const;
      virtual void printUpperTitle(Cairo::RefPtr<Cairo::Context>&,
				   const GraphLayout&,
				   const GraphSize&,
				   const std::string&) const;
      virtual void printDownTitle(Cairo::RefPtr<Cairo::Context>&,
				  const GraphLayout&,
				  const GraphSize&,
				  const std::string&) const;
      virtual void printRightTitle(Cairo::RefPtr<Cairo::Context>&,
				   const GraphLayout&,
				   const GraphSize&,
				  const std::string&) const;
      virtual void printLeftTitle(Cairo::RefPtr<Cairo::Context>&,
				  const GraphLayout&,
				  const GraphSize&,
				  const std::string&) const;
      virtual void printXLabel(Cairo::RefPtr<Cairo::Context>&,
			       const GraphLayout&,
			       const GraphSize&,
			       const std::string&) const;
      virtual void printYLabel(Cairo::RefPtr<Cairo::Context>&,
			       const GraphLayout&,
			       const GraphSize&,
			       const std::string&) const;
      virtual void printX2Label(Cairo::RefPtr<Cairo::Context>&,
				const GraphLayout&,
				const GraphSize&,
				const std::string&) const;
      virtual void printY2Label(Cairo::RefPtr<Cairo::Context>&,
				const GraphLayout&,
				const GraphSize&,
				const std::string&) const;
      virtual void printXTics(Cairo::RefPtr<Cairo::Context>&,
			      const GraphLayout&,
			      const GraphSize&,
			      const std::map<double,std::string>&) const;
      virtual void printYTics(Cairo::RefPtr<Cairo::Context>&,
			      const GraphLayout&,
			      const GraphSize&,
			      const std::map<double,std::string>&) const;
      virtual void printX2Tics(Cairo::RefPtr<Cairo::Context>&,
			       const GraphLayout&,
			       const GraphSize&,
			       const std::map<double,std::string>&) const;
      virtual void printY2Tics(Cairo::RefPtr<Cairo::Context>&,
			       const GraphLayout&,
			       const GraphSize&,
			       const std::map<double,std::string>&) const;
      virtual void getGraphBorders(unsigned short&,unsigned short&,
				   unsigned short&,unsigned short&) const;
      virtual void drawXAxis(Cairo::RefPtr<Cairo::Context>&,
			     const GraphLayout&,
			     const GraphSize&) const;
      virtual void drawGrid(Cairo::RefPtr<Cairo::Context>&,
			    const GraphLayout&,
			    const GraphSize&,
			    const bool,
			    const unsigned short,
			    const std::map<double,std::string>&,
			    const std::map<double,std::string>&,
			    const std::map<double,std::string>&,
			    const std::map<double,std::string>&,
			    const double,const double,
			    const double,const double,
			    const double,const double,
			    const double,const double,
			    const bool, const bool,
			    const bool,const bool) const;
      virtual void drawYAxis(Cairo::RefPtr<Cairo::Context>&,
			     const GraphLayout&,
			     const GraphSize&) const;
      virtual void drawGraphBorder(Cairo::RefPtr<Cairo::Context>&,
				   const GraphLayout&,
				   const GraphSize&) const;
      virtual void drawForeGround(Cairo::RefPtr<Cairo::Context>&,
				  const GraphLayout&,
				  const GraphSize&) const;
      virtual void drawBackGround(Cairo::RefPtr<Cairo::Context>&,
				  const GraphLayout&,
				  const GraphSize&) const;
      virtual void drawGraphForeGround(Cairo::RefPtr<Cairo::Context>&,
				       const GraphLayout&,
				       const GraphSize&) const;
      virtual void drawGraphBackGround(Cairo::RefPtr<Cairo::Context>&,
				       const GraphLayout&,
				       const GraphSize&) const;
      void drawCurve(Cairo::RefPtr<Cairo::Context>&,
		     const double,
		     const double,
		     const double,
		     const double,
		     const GraphSize&,
		     const std::vector<Point>&,
		     const Curve::Style,
		     const unsigned short) const;
      void drawCurve(Cairo::RefPtr<Cairo::Context>&,
		     const double,
		     const double,
		     const double,
		     const double,
		     const GraphSize&,
		     const std::vector<Point>&,
		     const Curve::Style,
		     const Curve::Color,
		     const unsigned short) const;
      virtual void printLabel(Cairo::RefPtr<Cairo::Context>&,
			      const double,
			      const double,
			      const std::string&) const;
      virtual void drawArrow(Cairo::RefPtr<Cairo::Context>&,
			     const double,
			     const double,
			     const double,
			     const double,
			     const ArrowStyle) const;
      virtual void printLegend(Cairo::RefPtr<Cairo::Context>&,
			       const GraphLayout&,
			       const GraphSize&,
			       const std::string&,
			       const Curve::Style,
			       const unsigned short) const;
      virtual void printLegend(Cairo::RefPtr<Cairo::Context>&,
			       const GraphLayout&,
			       const GraphSize&,
			       const std::string&,
			       const Curve::Style,
			       const Curve::Color,
			       const unsigned short) const;
      virtual unsigned short getXLabelHeight(Cairo::RefPtr<Cairo::Context>&,
	      				   const std::string&) const;
      virtual unsigned short getX2LabelHeight(Cairo::RefPtr<Cairo::Context>&,
					      const std::string&) const;
      virtual unsigned short getYLabelWidth(Cairo::RefPtr<Cairo::Context>&,
					    const std::string&) const;
      virtual unsigned short getY2LabelWidth(Cairo::RefPtr<Cairo::Context>&,
					     const std::string&) const;
      
      virtual unsigned short getDownTitleHeight(Cairo::RefPtr<Cairo::Context>&,
						const std::string&) const;
      virtual unsigned short getUpperTitleHeight(Cairo::RefPtr<Cairo::Context>&,
						 const std::string&) const;
      virtual unsigned short getLeftTitleWidth(Cairo::RefPtr<Cairo::Context>&,
					       const std::string&) const;
      virtual unsigned short getRightTitleWidth(Cairo::RefPtr<Cairo::Context>&,
						const std::string&) const;
      
      virtual ~StandardGraphTheme();
    protected :
      void
      drawHorizontalGridMark(Cairo::RefPtr<Cairo::Context>&,
			     const GraphLayout&,
			     const GraphSize&,
			     const std::map<double,std::string>&,
			     const double,const double) const;
      void
      drawVerticalGridMark(Cairo::RefPtr<Cairo::Context>&,
			   const GraphLayout&,
			   const GraphSize&,
			   const std::map<double,std::string>&,
			   const double,const double) const;
      void
      drawHorizontalGrid(Cairo::RefPtr<Cairo::Context>&,
			 const GraphLayout&,
			 const GraphSize&,
			 const std::map<double,std::string>&,
			 const double,const double) const;
      void
      drawVerticalGrid(Cairo::RefPtr<Cairo::Context>&,
		       const GraphLayout&,
		       const GraphSize&,
		       const std::map<double,std::string>&,
		       const double,const double) const;
      void drawCurveWithLines(Cairo::RefPtr<Cairo::Context>&,
			      const double,
			      const double,
			      const double,
			      const double,
			      const std::vector<Point>&) const;
      void drawCurveWithDots(Cairo::RefPtr<Cairo::Context>&,
			     const double,
			     const double,
			     const double,
			     const double,
			     const std::vector<Point>&) const;
      void drawCurveWithSquares(Cairo::RefPtr<Cairo::Context>&,
				const double,
				const double,
				const double,
				const double,
				const std::vector<Point>&) const;
      void drawCurveWithTriangles(Cairo::RefPtr<Cairo::Context>&,
				  const double,
				  const double,
				  const double,
				  const double,
				  const std::vector<Point>&) const;
      void drawCurveWithCrosses(Cairo::RefPtr<Cairo::Context>&,
				const double,
				const double,
				const double,
				const double,
				const std::vector<Point>&) const;
      void drawCurveWithPoints(Cairo::RefPtr<Cairo::Context>&,
			       const double,
			       const double,
			       const double,
			       const double,
			       const std::vector<Point>&) const;
      void drawCurveWithDiamonds(Cairo::RefPtr<Cairo::Context>&,
				 const double,
				 const double,
				 const double,
				 const double,
				 const std::vector<Point>&) const;
    protected:
      virtual void
      drawCurveLegend(Cairo::RefPtr<Cairo::Context>&,
		      const Curve::Color,
		      const Curve::Style,
		      const unsigned short,
		      const unsigned short) const;
    private:
      static const double defaultRedColors[3];
      static const double defaultGreenColors[3];
      static const double defaultBlueColors[3];
      static const unsigned short defaultColorsNumber;
    }; // end of struct StandardGraphTheme

  } // end of namespace graphics

} // end of namespace tfel

#endif /* _LIB_TFEL_STANDARDGRAPHTHEME_HXX */

