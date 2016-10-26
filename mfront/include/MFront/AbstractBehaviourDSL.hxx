/*!
 * \file   mfront/include/MFront/AbstractBehaviourDSL.hxx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   October 23, 2014
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_MFRONT_ABSTRACTBEHAVIOURDSL_HXX_
#define LIB_MFRONT_ABSTRACTBEHAVIOURDSL_HXX_ 

#include<memory>
#include<iosfwd>
#include"MFront/MFrontConfig.hxx"
#include"TFEL/Material/ModellingHypothesis.hxx"

#include"MFront/AbstractDSL.hxx"
#include"MFront/BehaviourDescription.hxx"

namespace mfront{

  // forward declaration
  struct MaterialPropertyDescription;

  /*!
   * Interface class for all domain specific languages.
   */
  struct MFRONT_VISIBILITY_EXPORT AbstractBehaviourDSL
    : public virtual AbstractDSL
  {
    //! a simple alias
    using MaterialPropertyInput =
      BehaviourDescription::MaterialPropertyInput;
    //! constructor
    AbstractBehaviourDSL() = default;
    //! a simple alias
    using ModellingHypothesis = tfel::material::ModellingHypothesis;
    //! a simple alias
    using Hypothesis =  ModellingHypothesis::Hypothesis;
    //! \return the target of the dsl
    virtual DSLTarget getTargetType(void) const override final;
    //! \return the behaviour description
    virtual const BehaviourDescription&
    getBehaviourDescription(void) const = 0;
    /*!
     * \return the list of hypothesis a priori supported by
     * the parser.
     *
     * To enable other hypothesis or restrict the hypotheses
     * supported, the user must use the `@ModellingHypothesis` or
     * `@ModellingHypotheses` keywords.
     */
    virtual std::set<Hypothesis>
    getDefaultModellingHypotheses(void) const = 0;
    /*!
     * \brief write the call to a material property
     * \param[out] out: output stream
     * \param[in]  m:   material property description
     * \param[in]  f:   function converting input variable name.
     * The function f can be used to specify how evaluate a variable value.
     * For example, if we want to evaluate the variable name 'V' at
     * the end of the time step, we could make f return V+dV
     */
    virtual void
    writeMaterialPropertyEvaluation(std::ostream&,
				    const BehaviourDescription::MaterialProperty&,
				    std::function<std::string(const MaterialPropertyInput&)>&) = 0;
    /*!
     * \brief This function handles a material property treated as a
     * dependency of the current file.
     *
     * This function:
     * - analyse the given file using the MaterialPropertyDSL
     * - register the function name generated by the MFront interface
     * - add the function name to the list of material laws used by
     *   the current file
     * - declared the headers generated by the MFront interface for inclusion
     * - launch mfront in a sub-process to generate the source files
     *   associated with this material property and have them compiled
     *   when mandatory (done by the callMFront method).
     *
     * \param[in] f : file in which the material law is
     * implemented. This must be the full path.
     */
    virtual std::shared_ptr<MaterialPropertyDescription>
    handleMaterialPropertyDescription(const std::string&) = 0;
    /*!
     * \return true if the given modelling hypothesis is handled by
     * the parser
     *
     * Some parsers have restrictions on the modelling hypotheses
     * supported. For example, the isotropic behaviours were not able
     * to handle plane stress hypotheses when this comment was
     * written(but it was planned, so this comment may be outdated
     * now).
     *
     * The fact that this method returns true means that the user
     * *can* provide code to support this modelling hypothesis. For
     * example, to support plane stress in RungeKutta and Implicit
     * parsers, the user must provide some hand-crafted code. He must
     * enable this modelling hypothesis by calling explicitely
     * `@ModellingHypothesis` or `@ModellingHypotheses` keywords.
     */
    virtual bool
    isModellingHypothesisSupported(const Hypothesis) const = 0;
    //! destructor
    virtual ~AbstractBehaviourDSL();
  };

} // end of namespace mfront

#endif /* LIB_MFRONT_ABSTRACTBEHAVIOURDSL_HXX_ */

