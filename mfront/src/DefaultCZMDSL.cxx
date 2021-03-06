/*!
 * \file   mfront/src/DefaultCZMDSL.cxx
 * \brief  
 * \author Thomas Helfer
 * \date   08 nov 2006
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#include<string>
#include<fstream>
#include<stdexcept>

#include"MFront/AbstractBehaviourInterface.hxx"
#include"MFront/BehaviourInterfaceFactory.hxx"
#include"MFront/DefaultCZMDSL.hxx"

namespace mfront{

  DefaultCZMDSL::DefaultCZMDSL(){
    const auto h = ModellingHypothesis::UNDEFINEDHYPOTHESIS;
    this->mb.setDSLName("DefaultCZM");
    this->mb.declareAsACohesiveZoneModel();
    this->mb.addLocalVariable(h,VariableDescription("real&","u_n",1u,0u));
    this->mb.addLocalVariable(h,VariableDescription("real&","du_n",1u,0u));
    this->mb.addLocalVariable(h,VariableDescription("real&","t_n",1u,0u));    
    this->mb.addLocalVariable(h,VariableDescription("tfel::math::Expr<tfel::math::tvector<N-1,real>,tfel::math::TinyVectorFromTinyVectorViewExpr<N-1,N,1,real,false> >","u_t",1u,0u));
    this->mb.addLocalVariable(h,VariableDescription("tfel::math::Expr<tfel::math::tvector<N-1,real>,tfel::math::TinyVectorFromTinyVectorViewExpr<N-1,N,1,real,false> >","du_t",1u,0u));
    this->mb.addLocalVariable(h,VariableDescription("tfel::math::Expr<tfel::math::tvector<N-1,real>,tfel::math::TinyVectorFromTinyVectorViewExpr<N-1,N,1,real,false> >","t_t",1u,0u));
    this->mb.addLocalVariable(h,VariableDescription("real&","Dt_nn",1u,0u));
    this->mb.addLocalVariable(h,VariableDescription("tfel::math::tmatrix_row_view<N,N,0,1,N-1,real>","Dt_nt",1u,0u));
    this->mb.addLocalVariable(h,VariableDescription("tfel::math::tmatrix_column_view<N,N,0,1,N-1,real>","Dt_tn",1u,0u));
    this->mb.addLocalVariable(h,VariableDescription("tfel::math::tmatrix_submatrix_view<N,N,1,1,N-1,N-1,real>","Dt_tt",1u,0u));
  }

  std::string DefaultCZMDSL::getDescription(){
    return "this parser is the most generic one as it does not make any restriction "
           "on the behaviour or the integration method that may be used";
  } // end of DefaultCZMDSL::getDescription
  
  std::string DefaultCZMDSL::getName(){
    return "DefaultCZMDSL";
  }

  BehaviourDSLDescription DefaultCZMDSL::getBehaviourDSLDescription() const {
    auto d = BehaviourDSLDescription{};
    d.behaviourType =
        tfel::material::MechanicalBehaviourBase::COHESIVEZONEMODEL;
    d.integrationScheme = IntegrationScheme::USERDEFINEDSCHEME;
    d.typicalCodeBlocks = {BehaviourData::ComputePredictionOperator,
                           BehaviourData::Integrator,
                           BehaviourData::ComputeTangentOperator};
    d.allowCrystalStructureDefinition = false;
    d.minimalMFrontFileBody = "@Integrator{}\n\n";
    return d;
  }  // end of DefaultCZMDSL::getBehaviourDSLDescription

  void DefaultCZMDSL::writeBehaviourParserSpecificIncludes(std::ostream& os) const{
    DefaultDSLBase::writeBehaviourParserSpecificIncludes(os);
    os << "#include\"TFEL/Math/tmatrix.hxx\"\n"
       << "#include\"TFEL/Math/tvector.hxx\"\n"
       << "#include\"TFEL/Math/Vector/tvectorIO.hxx\"\n"
       << "#include\"TFEL/Math/Matrix/tmatrixIO.hxx\"\n";
  } // end of DefaultCZMDSL::writeBehaviourParserSpecificIncludes

  std::string DefaultCZMDSL::getLocalVariablesInitializers(const Hypothesis) const{
    return "u_n(this->u(0)),\ndu_n(this->du(0)),\nt_n(this->t(0)),\n"
      "u_t(this->u),\ndu_t(this->du),\nt_t(this->t),\n"
      "Dt_nn(this->Dt(0,0)),\nDt_nt(this->Dt),\nDt_tn(this->Dt),\nDt_tt(this->Dt)";
  } // end of DefaultCZMDSL::getLocalVariablesInitializers

  
  DefaultCZMDSL::~DefaultCZMDSL() = default;

} // end of namespace mfront  
