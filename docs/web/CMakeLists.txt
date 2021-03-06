macro(pandoc_html file)
  ADD_CUSTOM_COMMAND(
    OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${file}.html
    DEPENDS   ${CMAKE_CURRENT_SOURCE_DIR}/${file}.md
    DEPENDS   ${CMAKE_CURRENT_SOURCE_DIR}/mfront-template.html
    DEPENDS   ${CMAKE_CURRENT_SOURCE_DIR}/css/main.css
    COMMAND   ${PANDOC}
    ARGS      -f markdown-markdown_in_html_blocks+tex_math_single_backslash+grid_tables
    ARGS      --filter pandoc-crossref -M crossrefYaml=${CMAKE_CURRENT_SOURCE_DIR}/pandoc-crossref.yaml
    ARGS      --bibliography=${CMAKE_CURRENT_SOURCE_DIR}/bibliography.bib --filter pandoc-citeproc
    ARGS      --template=${CMAKE_CURRENT_SOURCE_DIR}/mfront-template.html
    ARGS      --mathjax
    ARGS      --highlight-style=tango
    ARGS      --email-obfuscation=javascript
    ARGS       --default-image-extension=svg
    ARGS      ${ARGN}
    ARGS      ${CMAKE_CURRENT_SOURCE_DIR}/${file}.md -o ${file}.html)
  add_custom_target(${file}-html ALL DEPENDS ${file}.html)
  add_dependencies(website ${file}-html)
  if(TFEL_APPEND_SUFFIX)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${file}.html
      DESTINATION share/doc/tfel-${TFEL_SUFFIX}/web
      COMPONENT website)
  else(TFEL_APPEND_SUFFIX)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${file}.html
      DESTINATION share/doc/tfel/web
      COMPONENT website)
  endif(TFEL_APPEND_SUFFIX)
endmacro(pandoc_html)

add_custom_target(website)
add_dependencies(doc website)

pandoc_html(index "-c css/slideshow.css")
pandoc_html(search)
pandoc_html(faq "--toc")
pandoc_html(getting-started)
pandoc_html(interfaces)
pandoc_html(install)
pandoc_html(install-freebsd "-c css/slideshow.css")
pandoc_html(install-windows-msys)
pandoc_html(install-windows-Cast3M2017 "--toc")
pandoc_html(install-windows-VisualStudio)
pandoc_html(packages)
pandoc_html(about)
pandoc_html(svn)
pandoc_html(devel)
pandoc_html(mtest)
pandoc_html(mtest-python "--toc" "--toc-depth=3")
pandoc_html(tutorial "--toc" "--toc-depth=3")
pandoc_html(tutorial-spanish  "--toc" "--toc-depth=3")
pandoc_html(benchmark)
pandoc_html(news "-c css/slideshow.css")
pandoc_html(castem)
pandoc_html(castem-fr)
pandoc_html(cyrano "--toc" "--toc-depth=1"  "--number-sections")
pandoc_html(aster "--toc" "--toc-depth=1"  "-c css/slideshow.css")
pandoc_html(abaqus "-c css/slideshow.css")
pandoc_html(ansys "-c css/slideshow.css")
pandoc_html(calculix "-c css/slideshow.css")
pandoc_html(zmat)
pandoc_html(epx "-c css/slideshow.css")
pandoc_html(documentations)
pandoc_html(gallery  "--toc")
pandoc_html(glossary)
pandoc_html(material-properties)
pandoc_html(behaviours)
pandoc_html(implicit-dsl "--toc" "--toc-depth=3"  "--number-sections")
pandoc_html(models)
pandoc_html(parameters)
pandoc_html(publications)
pandoc_html(release-notes "--toc" "--toc-depth=1")
pandoc_html(math "--toc" "--toc-depth=2" "--number-sections")
pandoc_html(material "--toc" "--toc-depth=2")
pandoc_html(mfm)
pandoc_html(mfm-test-generator)
pandoc_html(mfront-doc)
pandoc_html(mfront-python "--toc" "--toc-depth=3")
pandoc_html(Norton-web)
pandoc_html(Norton-full)
pandoc_html(coverity-scan)
pandoc_html(drucker "--toc")
pandoc_html(drucker-prager-cap "--toc")
pandoc_html(hosford "--toc")
pandoc_html(barlat-yld2004 "--toc")
pandoc_html(greenplasticity "--toc")
pandoc_html(hyperelasticity "--toc")
pandoc_html(signorini "--toc" "--toc-depth=2" "-c css/slideshow.css")
pandoc_html(ogden "--toc" "--toc-depth=2")
pandoc_html(iwan "--toc" "--toc-depth=2")
pandoc_html(hyperviscoelasticity "--toc" "--toc-depth=2")
pandoc_html(IsotropicLinearHardeningPlasticity "--toc" "--toc-depth=2")
pandoc_html(orthotropiclinearhardeningplasticity "--toc" "--toc-depth=2")
pandoc_html(physical-constants)
pandoc_html(isotropicplasticityamstrongfrederickinematichardening "--toc" "--toc-depth=2")
pandoc_html(singlecrystal "--toc" "--toc-depth=2")
pandoc_html(finitestrainsinglecrystal "--toc" "--toc-depth=2")
pandoc_html(finitestrainsinglecrystal-huang "--toc" "--toc-depth=2")
pandoc_html(phasefield "--toc" "--toc-depth=2")
pandoc_html(release-notes-2.0.5 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.0   "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.0.1 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.0.2 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.0.3 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.0.4 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.0.5 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.0.6 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.1   "--toc" "--toc-depth=2" "--number-sections" "-c css/slideshow.css")
pandoc_html(release-notes-3.1.1 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.1.2 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.1.3 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.1.4 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.1.5 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.1.6 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.2   "--toc" "--toc-depth=2" "--number-sections" "-c css/slideshow.css")
pandoc_html(release-notes-3.2.1 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.2.2 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.2.3 "--toc" "--toc-depth=2")
pandoc_html(release-notes-3.3   "--toc" "--toc-depth=2" "--number-sections" "-c css/slideshow.css")
pandoc_html(release-notes-3.3.1   "--toc" "--toc-depth=2" "--number-sections" "-c css/slideshow.css")
pandoc_html(release-notes-3.4   "--toc" "--toc-depth=2" "--number-sections")
pandoc_html(theory  "--toc" "--toc-depth=2")
pandoc_html(tensors "--toc" "--toc-depth=2" "--number-sections")
pandoc_html(tfel-python "--toc" "--toc-depth=3")
pandoc_html(generic-behaviours-interface "--toc" "--toc-depth=3")
pandoc_html(sovs "--toc" "--toc-depth=2")
pandoc_html(unicode "--toc" "--toc-depth=2")
pandoc_html(RambergOsgoodNonLinearElasticity "--toc" "--toc-depth=2")
pandoc_html(MericCailletaudSingleCrystalPlasticity  "--toc" "--toc-depth=2")
pandoc_html(MohrCoulomb "--toc" "--toc-depth=2")
pandoc_html(FichantLaBorderieDamageBehaviour "--toc" "--toc-depth=2")
pandoc_html(LoadInducedThermalStrainBehaviourTorelli2018  "--toc" "--toc-depth=2")
pandoc_html(FichantLaBorderieDamageAndTorelliLoadInducedStrainBehaviour   "--toc" "--toc-depth=2")
pandoc_html(FischerBurmeister "--toc" "--toc-depth=2")
pandoc_html(TFELSystem "--toc" "--toc-depth=2")

# mfront keywords

pandoc_html(DefaultDSL-keywords "--toc" "--toc-depth=1")
pandoc_html(DefaultFiniteStrainDSL-keywords "--toc" "--toc-depth=1")
pandoc_html(DefaultCZMDSL-keywords "--toc" "--toc-depth=1")
pandoc_html(Implicit-keywords "--toc" "--toc-depth=1")
pandoc_html(ImplicitFiniteStrain-keywords "--toc" "--toc-depth=1")
pandoc_html(ImplicitII-keywords "--toc" "--toc-depth=1")
pandoc_html(IsotropicMisesCreep-keywords "--toc" "--toc-depth=1")
pandoc_html(IsotropicPlasticMisesFlow-keywords "--toc" "--toc-depth=1")
pandoc_html(IsotropicStrainHardeningMisesCreep-keywords "--toc" "--toc-depth=1")
pandoc_html(MaterialLaw-keywords "--toc" "--toc-depth=1")
pandoc_html(Model-keywords "--toc" "--toc-depth=1")
pandoc_html(MultipleIsotropicMisesFlows-keywords "--toc" "--toc-depth=1")
pandoc_html(RungeKutta-keywords "--toc" "--toc-depth=1")
pandoc_html(BehaviourBricks "--toc" "--toc-depth=2")
pandoc_html(DDIF2Brick "--toc" "--toc-depth=2")
pandoc_html(StandardElastoViscoPlasticityBrick "--toc" "--toc-depth=2")
pandoc_html(ExtendingStandardElastoViscoPlasticityBrick-StressCriterion "--toc" "--toc-depth=2")
pandoc_html(HookeStressPotential "--toc" "--toc-depth=2")
pandoc_html(DDIF2StressPotential "--toc" "--toc-depth=2")

# mtest keywords

pandoc_html(MTest-keywords "--toc" "--toc-depth=1")

if(TFEL_APPEND_SUFFIX)
  install(DIRECTORY js css doc img media downloads cxx mfront scripts
    DESTINATION share/doc/tfel-${TFEL_SUFFIX}/web
    COMPONENT website
    PATTERN ".svn" EXCLUDE)
  install(FILES 404.html apple-touch-icon-precomposed.png 
    CHANGELOG.md CONTRIBUTING.md crossdomain.xml favicon.ico
    humans.txt LICENSE.md README.md robots.txt TODO.md
    DESTINATION share/doc/tfel-${TFEL_SUFFIX}/web
    COMPONENT website)
else(TFEL_APPEND_SUFFIX)
  install(DIRECTORY js css doc img media downloads cxx mfront scripts
    DESTINATION share/doc/tfel/web
    COMPONENT website
    PATTERN ".svn" EXCLUDE)
  install(FILES 404.html apple-touch-icon-precomposed.png 
    CHANGELOG.md CONTRIBUTING.md crossdomain.xml favicon.ico
    humans.txt LICENSE.md README.md robots.txt TODO.md
    DESTINATION share/doc/tfel/web
    COMPONENT website)
endif(TFEL_APPEND_SUFFIX)
