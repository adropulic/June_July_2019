/*******************************************************************/
/* makeRatesPlot.C                                                 */
/* ROOT macro                                                      */
/* Usage: root -l -b -q makeRatesPlot.C                            */
/*******************************************************************/

#include "calculateRates.C"

#include "../base_code_for_plots/CMS_lumi.h"
#include "../base_code_for_plots/tdrstyle.C"

void plotHists(TH1F* h1, TString h1Label, 
	       TH1F* h2, TString h2Label,
	       TH1F* h3, TString h3Label,
	       TString filename,
               TString outputDir);

void plotFiveRates(TH1F* h1, TString h1Label, int c1,
		   TH1F* h2, TString h2Label, int c2,
		   TH1F* h3, TString h3Label, int c3,
		   TH1F* h4, TString h4Label, int c4,
		   TH1F* h5, TString h5Label, int c5,
		   float xMin, float xMax,
		   float yMin, float yMax,
		   TString legendTitle,
		   TString filename,
		   TString outputDir);

/*********************************************************************/

/* Plots rates (x-axis: L1 Tau Pt) and saves to .png file. */

void makeRatesPlot(void)
{
  gROOT->ProcessLine(".L calculateRates.C");

  /* Specify paths/directories for input files. */
  TString rootFileDirectory = "../ntuples/newTauZL1PtCut10/SingleNeutrino-200PU.root";
  //going to use ZeroBias here instead 
  TString outputDirectory = "plots/";

  /*******************************************************/
  /* Rates as a function of l1Pt                         */
  /*******************************************************/

  /* Tau rates full detector */
  TString l1PtPath = "L1TauAnalyzerRates/l1Tau_pt";
  TH1F* tauTight  = calculateRates("L1TauAnalyzerRates/l1TauIsoTight_pt",  l1PtPath, rootFileDirectory);
  TH1F* tauMedium = calculateRates("L1TauAnalyzerRates/l1TauIsoMedium_pt", l1PtPath, rootFileDirectory);
  TH1F* tauLoose  = calculateRates("L1TauAnalyzerRates/l1TauIsoLoose_pt",  l1PtPath, rootFileDirectory);
  TH1F* tauVLoose = calculateRates("L1TauAnalyzerRates/l1TauIsoVLoose_pt", l1PtPath, rootFileDirectory);
  TH1F* tauNoBDT  = calculateRates("L1TauAnalyzerRates/l1Tau_pt",          l1PtPath, rootFileDirectory);

  plotFiveRates(
		tauNoBDT, "L1 Reconstruction", kPink+7,
		tauVLoose, "Very Loose", kTeal-8,
		tauLoose, "Loose", kTeal-6,
		tauMedium, "Medium", kAzure-9,
		tauTight, "Tight", kAzure+2,
		18.0, 60.0,
		10.0, 130000,
		"Tau Rate (Full Detector)",
		"rates-tau-PF_200PU_deltaZ5cm_fullDetector.png",
		"plots/");

  /* Tau rates: eta < 2.4 */
  l1PtPath = "L1TauAnalyzerRates/l1Tau_pt_eta2p4";
  TH1F* tauTight2p4 = calculateRates("L1TauAnalyzerRates/l1TauIsoTight_pt_eta2p4", l1PtPath, rootFileDirectory);
  TH1F* tauMedium2p4 = calculateRates("L1TauAnalyzerRates/l1TauIsoMedium_pt_eta2p4", l1PtPath, rootFileDirectory);
  TH1F* tauLoose2p4 = calculateRates("L1TauAnalyzerRates/l1TauIsoLoose_pt_eta2p4", l1PtPath, rootFileDirectory);
  TH1F* tauVLoose2p4 = calculateRates("L1TauAnalyzerRates/l1TauIsoVLoose_pt_eta2p4", l1PtPath, rootFileDirectory);
  TH1F* tauNoBDT2p4 = calculateRates("L1TauAnalyzerRates/l1Tau_pt_eta2p4", l1PtPath, rootFileDirectory);
  
  plotFiveRates(
		tauNoBDT2p4, "L1 Reconstruction", kPink+7,
                tauVLoose2p4, "Very Loose", kTeal-8,
                tauLoose2p4, "Loose", kTeal-6,
                tauMedium2p4, "Medium", kAzure-9,
                tauTight2p4, "Tight", kAzure+2,
                18.0, 60.0,
                10.0, 130000,
                "Tau Rate (Barrel)",
                "rates-tau-PF_200PU_deltaZ5cm_Barrel.png",
                "plots/");

  /* Di-tau rates full detector */
  TString l1DiTauPtPath = "L1TauAnalyzerRates/l1DiTau_pt";
  TH1F* diTight  = calculateRates("L1TauAnalyzerRates/l1DiTauIsoTight_pt", l1DiTauPtPath,  rootFileDirectory);
  TH1F* diMedium = calculateRates("L1TauAnalyzerRates/l1DiTauIsoMedium_pt", l1DiTauPtPath, rootFileDirectory);
  TH1F* diLoose  = calculateRates("L1TauAnalyzerRates/l1DiTauIsoLoose_pt", l1DiTauPtPath, rootFileDirectory);
  TH1F* diVLoose = calculateRates("L1TauAnalyzerRates/l1DiTauIsoVLoose_pt", l1DiTauPtPath, rootFileDirectory);
  TH1F* diNoBDT = calculateRates("L1TauAnalyzerRates/l1DiTau_pt", l1DiTauPtPath, rootFileDirectory);

  plotFiveRates(
		diNoBDT, "L1 Reconstruction", kOrange+7,
		diVLoose, "Very Loose", kAzure+6,
		diLoose, "Loose", kAzure+2,
		diMedium, "Medium", kPink+6,
		diTight, "Tight", kPink+8,
		18.0, 60.0, 5.0, 200000,
		"DiTau Rate, Full Detector",
		"rates-DiTau-PF_200PU_deltaZ5cm_fullDetector.png",
		"plots/");

  /* Di-tau rates: eta < 2.4 */
  l1DiTauPtPath = "L1TauAnalyzerRates/l1DiTau_pt_eta2p4";
  TH1F* diTight2p4 = calculateRates("L1TauAnalyzerRates/l1DiTauIsoTight_pt_eta2p4", l1DiTauPtPath,  rootFileDirectory);
  TH1F* diMedium2p4 = calculateRates("L1TauAnalyzerRates/l1DiTauIsoMedium_pt_eta2p4", l1DiTauPtPath,  rootFileDirectory);
  TH1F* diLoose2p4 = calculateRates("L1TauAnalyzerRates/l1DiTauIsoLoose_pt_eta2p4", l1DiTauPtPath,  rootFileDirectory);
  TH1F* diVLoose2p4 = calculateRates("L1TauAnalyzerRates/l1DiTauIsoVLoose_pt_eta2p4", l1DiTauPtPath,  rootFileDirectory);
  TH1F* diNoBDT2p4 = calculateRates("L1TauAnalyzerRates/l1DiTau_pt_eta2p4", l1DiTauPtPath,  rootFileDirectory);

  plotFiveRates(
                diNoBDT2p4, "L1 Reconstruction", kOrange+7,
		diVLoose2p4, "Very Loose", kAzure+6,
		diLoose2p4, "Loose", kAzure+2,
		diMedium2p4, "Medium", kPink+6,
		diTight2p4, "Tight", kPink+8,
		18.0, 60.0, 5.0, 200000,
                "DiTau Rate, Barrel",
		"rates-DiTau-PF_200PU_deltaZ5cm_barrel.png",
		"plots/");
}

/*********************************************************************/

/* Plot five histograms with rates, with the labels h1Label and line
   color int c1 etc. If there's a way to do this without hard-coding
   five histograms in the argument, I'd love to see it... */

void plotFiveRates(TH1F* h1, TString h1Label, int c1,
		   TH1F* h2, TString h2Label, int c2,
		   TH1F* h3, TString h3Label, int c3,
		   TH1F* h4, TString h4Label, int c4,
		   TH1F* h5, TString h5Label, int c5,
		   float xMin, float xMax,
		   float yMin, float yMax,
		   TString legendTitle,
		   TString filename,
		   TString outputDir)
{
  /*******************************************************/
  /* plotting                                            */
  /*******************************************************/
  setTDRStyle();
  TCanvas* Tcan = new TCanvas("Tcan","", 100, 20, 1000, 1000);
  TLegend* leg = new TLegend(0.50, 0.6, 0.90, 0.90);
  Tcan->SetGrid();

  Tcan->cd();     /* Set current canvas */
  Tcan->SetFillColor(0);
  applyLegStyle(leg);

  h1->SetLineWidth(3);
  h1->SetLineColor(c1);

  h2->SetLineWidth(3);
  h2->SetLineColor(c2);

  h3->SetLineWidth(3);
  h3->SetLineColor(c3);

  h4->SetLineWidth(3);
  h4->SetLineColor(c4);

  h5->SetLineWidth(3);
  h5->SetLineColor(c5);

  /* Set x-axis limits */
  h1->Draw("");
  h2->Draw("SAME");
  h3->Draw("SAME");
  h4->Draw("SAME");
  h5->Draw("SAME");

  h1->GetXaxis()->SetRangeUser(xMin, xMax);
  h1->GetYaxis()->SetRangeUser(yMin, yMax);
  h1->GetXaxis()->SetTitle("Level-1 #tau_{H} p_{T} [GeV]");
  h1->GetYaxis()->SetTitle("Rate [kHz]");
  h1->GetXaxis()->SetTitleSize(0.06); // default is 0.03                                                                                                        
  h1->GetYaxis()->SetTitleSize(0.06);


  Tcan->SetLogy();

  /* Customize legend */
  leg->SetHeader(legendTitle);
  leg->AddEntry(h1, h1Label, "l");
  leg->AddEntry(h2, h2Label, "l");
  leg->AddEntry(h3, h3Label, "l");
  leg->AddEntry(h4, h4Label, "l");
  leg->AddEntry(h5, h5Label, "l");

  gStyle->SetLegendFont(20);
  leg->Draw();

  Tcan->cd();
  Tcan->SaveAs(outputDir+filename);

}


/*********************************************************************/

/* Plots Hist. */

void plotHists(TH1F* h1, TString h1Label,
               TH1F* h2, TString h2Label,
               TH1F* h3, TString h3Label,
	       TString filename,
	       TString outputDir)
{
  /*******************************************************/
  /* plotting                                            */
  /*******************************************************/
  setTDRStyle();
  TCanvas* Tcan = new TCanvas("Tcan","", 100, 20, 1000, 800);
  TLegend* leg = new TLegend(0.60,0.75,0.85,0.9);
  Tcan->SetGrid();

  Tcan->cd();     /* Set current canvas */
  Tcan->SetFillColor(0);
  leg = new TLegend(0.55, 0.2, 0.90, 0.5);
  applyLegStyle(leg);

  h1->SetMarkerColor(kViolet-5);
  h1->SetLineWidth(2);
  h1->SetLineColor(kViolet-5);

  h2->SetMarkerColor(kAzure+7);
  h2->SetLineWidth(2);
  h2->SetLineColor(kAzure+7);

  h3->SetMarkerColor(kOrange+7);
  h3->SetLineWidth(2);
  h3->SetLineColor(kOrange+7);

  /* Set x-axis limits */
  h1->GetXaxis()->SetRangeUser(0.0, 90.0);
  
  h1->Draw("");
  h2->Draw("SAME");
  h3->Draw("SAME");  

  h1->GetXaxis()->SetTitle("L1 Tau p_{T} [GeV]");
  h1->GetYaxis()->SetTitle("Rate [Hz]");
  h1->GetXaxis()->SetTitleSize(0.06); // default is 0.03  
  h1->GetYaxis()->SetTitleSize(0.06);

  
  Tcan->SetLogy();

  /* Customize legend */
  leg->SetHeader("Phase 2 L1 Taus");
  leg->AddEntry(h1, h1Label, "l");
  leg->AddEntry(h2, h2Label, "l");
  leg->AddEntry(h3, h3Label, "l");

  gStyle->SetLegendFont(20);
  leg->Draw();

  Tcan->cd();
  Tcan->SaveAs(outputDir+filename);

}

/*********************************************************************/
