/*!
 * \file   include/MFront/BehaviourBrick/PorosityNucleationModel.hxx
 * \brief
 * \author Thomas Helfer
 * \date   15/03/2018
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#ifndef LIB_MFRONT_BEHAVIOURBRICK_POROSITYNUCLEATIONMODEL_HXX
#define LIB_MFRONT_BEHAVIOURBRICK_POROSITYNUCLEATIONMODEL_HXX

#include <memory>
#include "TFEL/Material/ModellingHypothesis.hxx"
#include "MFront/MFrontConfig.hxx"
#include "MFront/BehaviourDescription.hxx"

namespace tfel {
  namespace utilities {
    // forward declaration
    struct Data;
  }  // end of namespace utilities
}  // end of namespace tfel

namespace mfront {

  // forward declaration
  struct AbstractBehaviourDSL;

  namespace bbrick {

    // forward declaration
    struct StressPotential;
    // forward declaration
    struct InelasticFlow;
    // forward declaration
    struct OptionDescription;

    //! \brief class describing an inelastic flow.
    struct MFRONT_VISIBILITY_EXPORT PorosityNucleationModel {
      //! a simple alias
      using Data = tfel::utilities::Data;
      //! a simple alias
      using DataMap = std::map<std::string, Data>;
      //! a simple alias
      using ModellingHypothesis = tfel::material::ModellingHypothesis;
      /*!
       * \return the name of a variable from a base name and the nucleation model id.
       * \param[in] n: base name
       * \param[in] id: nucleation model id
       */
      static std::string getVariableId(const std::string&, const std::string&);
      /*!
       * \param[in,out] bd: behaviour description
       * \param[in,out] dsl: abstract behaviour dsl
       * \param[in] id: porosity nucleation model id
       * \param[in] d: options
       */
      virtual void initialize(BehaviourDescription&,
                              AbstractBehaviourDSL&,
                              const std::string&,
                              const DataMap&) = 0;
      //! \return the flow options
      virtual std::vector<OptionDescription> getOptions() const = 0;
      /*!
       * \brief complete the variable description
       * \param[in/out] bd: behaviour description
       * \param[in] dsl: abstract behaviour dsl
       * \param[in] iflows: list of inelastic flows and their associated ids
       * \param[in] id: porosity nucleation model id
       */
      virtual void completeVariableDeclaration(
          BehaviourDescription&,
          const AbstractBehaviourDSL&,
          const std::map<std::string, std::shared_ptr<bbrick::InelasticFlow>>&,
          const std::string&) const = 0;
      /*!
       * \brief method called at the end of the input file processing
       * \param[in] dsl: abstract behaviour dsl
       * \param[in] bd: behaviour description
       * \param[in] sp: stress potential
       * \param[in] iflows: list of inelastic flows and their associated ids
       * \param[in] id: porosity nucleation model id
       */
      virtual void endTreatment(
          BehaviourDescription&,
          const AbstractBehaviourDSL&,
          const StressPotential&,
          const std::map<std::string, std::shared_ptr<bbrick::InelasticFlow>>&,
          const std::string&) const = 0;
      //! destructor
      virtual ~PorosityNucleationModel();

    };  // end of struct PorosityNucleationModel

  }  // end of namespace bbrick

}  // end of namespace mfront

#endif /* LIB_MFRONT_BEHAVIOURBRICK_POROSITYNUCLEATIONMODEL_HXX */
