#include "Begin_3LepMET.h"

void Begin_3LepMET()
{
    //==============================================
    // Begin_3LepMET:
    // This function gets called prior to the event looping.
    // This is where one declares variables, histograms, event selections for the category 3LepMET.
    //==============================================

    // Create variables used in this category.
    // Please follow the convention of <category>_<varname> structure.
    ana.tx.createBranch<int>("3LepMET_intVar1");
    ana.tx.createBranch<float>("3LepMET_floatVar1");
    ana.tx.createBranch<LorentzVector>("3LepMET_LVVar1");

    // Define selections
    // CommonCut will contain selections that should be common to all categories, starting from this cut, add cuts for this category of the analysis.
    ana.cutflow.getCut("CommonCut");
    ana.cutflow.addCutToLastActiveCut("Cut_3LepMET_Preselection", [&]() { return ana.tx.getBranch<LorentzVector>("3LepMET_LVVar1").pt() > 25.;}, [&]() { return ana.tx.getBranch<float>("3LepMET_floatVar1"); } );

    // Create histograms used in this category.
    // Please follow the convention of h_<category>_<varname> structure.
    // N.B. Using nbins of size 180 or 360 can provide flexibility as it can be rebinned easily, as 180, 360 are highly composite numbers.
    RooUtil::Histograms hists_3LepMET;
    hists_3LepMET.addHistogram("h_3LepMET_intVar1", 10, 0, 10, [&]() { return ana.tx.getBranch<int>("3LepMET_intVar1"); } );
    hists_3LepMET.addHistogram("h_3LepMET_floatVar1", 180, 0, 500, [&]() { return ana.tx.getBranch<float>("3LepMET_floatVar1"); } );
    hists_3LepMET.addHistogram("h_3LepMET_LVVar1_Pt", 180, 0, 150, [&]() { return ana.tx.getBranch<LorentzVector>("3LepMET_LVVar1").pt(); } );

    // Now book cutflow histogram (could be commented out if user does not want.)
    // N.B. Cutflow histogramming can be CPU consuming.
    ana.cutflow.bookCutflows();

    // Book histograms to cuts that user wants for this category.
    ana.cutflow.bookHistogramsForCut(hists_3LepMET, "Cut_3LepMET_Preselection");
}
