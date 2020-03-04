/*******************************************************************/
/* makeEfficienciesPlot.C                                          */
/* ROOT macro                                                      */
/* Usage: root -l -b -q makeEfficienciesPlot.C                     */
/*******************************************************************/

#include "efficiencyHist.C"
#include "calculateEfficiency.C"
#include "calculateL1TrackEfficiency.C"
#include "calculatePFCandEfficiency.C"

#include <string>
/*********************************************************************/

/* Plots L1 tau efficiency for different BDT discriminant working
   points. */

void makeEfficienciesPlot(void)
{
  gROOT->ProcessLine(".L calculateEfficiency.C");

  /* Load the TTree. */
        //TString inputFilename_ZB = "/afs/cern.ch/work/a/addropul/ZeroBias_all.root";
	//does not have bdt disciminant in it yet
        //TFile *inputFile_ZB = new TFile(inputFilename_ZB.Data());
        //TTree *inputTree_ZB = (TTree*) inputFile_ZB->Get("l1NtupleProducer/Stage3Regions/efficiencyTree");
  TString treePath = "l1NtupleProducer/Stage3Regions/efficiencyTree";
  TString rootFileDirectory = "/afs/cern.ch/user/a/addropul/CMSSW_10_6_0_pre4/src/L1Trigger/Run3Ntuplizer/test/l1TNtuple-ZeroBias-testbdt.root";
  TString outputDirectory = "/afs/cern.ch/user/a/addropul/CMSSW_10_6_0_pre4/src/L1Trigger/Run3Ntuplizer/test/June_July_2019/efficiency_plots/plots";

  float xMin, xMax;
  TString recoCut, l1Cut;

  /*******************************************************/
  /* efficiency as a function of recoPt                  */
  /*******************************************************/

  xMin = 0;
  xMax = 100;
  recoCut = "recoPt_1>10 && recoPt_2>10";
  l1Cut   = "recoPt_1>10 && recoPt_2>10 && l1Pt_1>0 && l1Pt_2>0";
  
  TGraphAsymmErrors* recoPtVLoose = calculateEfficiency("recoPt_1", treePath, rootFileDirectory,
						     l1Cut + "&& (bdtDiscriminant>-0.353)",
						     recoCut, xMin, xMax, true);
  
 TGraphAsymmErrors* recoPtLoose = calculateEfficiency("recoPt_1", treePath, rootFileDirectory,
						       l1Cut + "&& (bdtDiscriminant>-0.308)",
						       recoCut, xMin, xMax, true);
  
  TGraphAsymmErrors* recoPtMedium = calculateEfficiency("recoPt_1", treePath, rootFileDirectory,
							l1Cut + "&& (bdtDiscriminant>-0.183)",
							recoCut, xMin, xMax, true);
  
  TGraphAsymmErrors* recoPtTight = calculateEfficiency("recoPt_1", treePath, rootFileDirectory,
						       l1Cut + "&& (bdtDiscriminant>-0.003)",
						       recoCut, xMin, xMax, true);


  TGraphAsymmErrors* recoPtNoBDT = calculateEfficiency("recoPt_1", treePath, rootFileDirectory,
						       l1Cut,
						       recoCut, xMin, xMax, true);



  plotFiveHists(
		recoPtNoBDT, "allDM", kAzure+1,
		recoPtTight, "allDM Tight", kBlue-3,
		recoPtMedium, "allDM Medium", kViolet-5,
		recoPtLoose, "allDM Loose", kPink+8,
		recoPtVLoose, "allDM VLoose", kPink+6,
		"Reco jet  p_{T} [GeV]",
		"VBFH #tau#tau",
		"eff_recoPt_PF.png",
		outputDirectory);

  /*******************************************************/
  /* efficiency as a function of recoEta                 */
  /*******************************************************/
  /*  xMin = -3;
  xMax = 3;
  
  recoCut = "recoPt>30 && genPt>20 && l1Track_pt>10 && genDM>9";
  l1Cut   = "recoPt>30 && genPt>20 && l1Track_pt>10 && genDM>9 && l1Pt>10";

  TGraphAsymmErrors* effVsRecoEta90 = calculateEfficiency("recoEta", treePath, rootFileDirectory,
							  l1Cut + "&& (l1BDTDisriminant > -0.0435867)",
							  recoCut, xMin, xMax, false);
  TGraphAsymmErrors* effVsRecoEta95 = calculateEfficiency("recoEta", treePath, rootFileDirectory,
                                                          l1Cut + "&& (l1BDTDisriminant > -0.0486184)",
							  recoCut, xMin, xMax, false);
  TGraphAsymmErrors* effVsRecoEtaNoBDT = calculateEfficiency("recoEta", treePath, rootFileDirectory, 
							     l1Cut,
							     recoCut, xMin, xMax, false);

  plotThreeHists(
		 effVsRecoEta90, "BDT Loose",
		 effVsRecoEta95, "BDT VLoose",
		 effVsRecoEtaNoBDT, "No BDT",
		 "Reco #tau_{H} #eta",
		 "Phase 2 L1 Taus (all #tau_{H} decay modes)",
		 "effVsRecoEta_allDM_l1TracksPt10.png",
		 outputDirectory);
  */
}


/*********************************************************************/
