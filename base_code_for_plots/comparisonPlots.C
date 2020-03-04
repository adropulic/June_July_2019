#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TF1.h"
#include <math.h>
#include <TEfficiency.h>
#include <TMath.h>
#include <TFormula.h>
#include <iostream>
#include <string>

#include <iostream>
#include <cmath>
#include "TLegend.h"
#include "TPad.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
#include "TF1.h"
#include "THStack.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TTree.h"
#include "TPaveText.h"
#include "tdrstyle.C"
#include "TStyle.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "CMS_lumi.h"

void applyPadStyle(TPad* pad1){
  pad1->SetFillColor(0);
  pad1->Draw();  pad1->cd();  pad1->SetLeftMargin(0.2);  pad1->SetBottomMargin(0.13); pad1->SetRightMargin(0.1);
  //pad1->SetGrid(); 
  pad1->SetGrid(10,10); 
}
void applyLegStyle(TLegend *leg){
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetHeader("");
  leg->SetShadowColor(0);
}

void comparisonPlots(TString variable, TString genCut, TString fakeCut, TString treePath, TString inputDirectory, TString outputDirectory, TString name, int bins, int low, int high){


  gROOT->LoadMacro("CMS_lumi.C");
  //gROOT->ProcessLine(".L ~/Documents/work/Analysis/PhaseIIStudies/2018/tdrstyle.C");
  //gROOT->ProcessLine(".L ~/Documents/work/Analysis/PhaseIIStudies/plotEfficiencyReturnASYM.C");
  //gROOT->ProcessLine(".L /Users/isobelojalvo/Documents/work/Analysis/Level1/tauSeedStudy/plotResolution.C");
  //gROOT->ProcessLine(".L /Users/isobelojalvo/Documents/work/Analysis/Level1/tauSeedStudy/plotTProfile.C");
  setTDRStyle();

  //int bins = 30;
  //int low = 0;
  //int high = 15;

  TFile *tauFile    = new TFile("dummy");
  TCanvas *Tcan= new TCanvas("Tcan","",100,20,800,600); Tcan->cd();  Tcan->SetFillColor(0);
  TPad* pad1 = new TPad("pad1","The pad",0,0.0,0.98,1);
  applyPadStyle(pad1);

  TLegend *leg = new TLegend(0.60,0.75,0.85,0.9);
  applyLegStyle(leg);

  TFile *file    = new TFile(inputDirectory);

  if(!file->IsOpen()||file==0){
    std::cout<<"ERROR FILE "<< inputDirectory + name<<" NOT FOUND; EXITING"<<std::endl;
    return 0;
  }

  //gStyle->SetOptFit(0);
  //gStyle->SetOptStat(0);
  //gStyle->SetEndErrorSize(0);
  //gStyle->SetErrorX(0.5);

  TTree* tree = (TTree*)file->Get(treePath);
  if(tree == 0){
    std::cout<<"ERROR Tau Tree is "<< tree<<" NOT FOUND; EXITING"<<std::endl;
    return 0;
  }

  TH1F * True = new TH1F("True","True",bins,low,high);
  tree->Draw(variable+">>+True", genCut);
  TH1F * Fake = new TH1F("Fake","Fake",bins,low,high);
  tree->Draw(variable+">>+Fake", fakeCut);  

  TH1F* ratio = True->Clone();
  ratio->Add(Fake,-1);
  
  ratio->Divide(Fake);
  
  True->SetLineWidth(2);
  True->SetLineColor(kBlue+2);
  True->SetFillStyle(3244);
  True->SetFillColor(kBlue+2);
  Fake->SetLineWidth(2);
  Fake->SetFillStyle(3001);  
  Fake->SetFillColor(kRed+2);
  Fake->SetLineColor(kRed+2);
  Fake->Scale(1/Fake->Integral());
  True->Scale(1/True->Integral());
  Tcan->SetLogy();
  pad1->SetLogy();
  //NoIso->Draw();
  Fake->Draw();
  True->Draw("same");
 
  Fake->GetXaxis()->SetTitle(variable);
  Fake->GetYaxis()->SetTitle("A.U.");

  float max = 10;
  if(Fake->GetXaxis()->GetBinCenter( Fake->GetMaximumBin() ) > True->GetXaxis()->GetBinCenter( True->GetMaximumBin() ) )
    max = Fake->GetXaxis()->GetBinCenter(Fake->GetMaximumBin());
  else 
    max = True->GetXaxis()->GetBinCenter(True->GetMaximumBin());
  
  std::cout<<"max: "<<max<<std::endl;
  Fake->SetMaximum(max*10);

  leg->SetHeader("MTD Level1 PF Taus");
  //leg->AddEntry(NoIso,"No Isolation","l");
  leg->AddEntry(True,"#tau_{h} Gen-Vis p_{T}>20 GeV","l");
  leg->AddEntry(Fake,"Fake Background","l");
  leg->Draw();

  Tcan->cd();
  //TPad* pad2 = new TPad("pad2","The lower pad",0,0,0.98,0.25);
  //applyPadStyle(pad2);
  //pad2->cd();
  //pad2->SetGrid(0,0); 

  //ratio->Draw("p");

  ratio->GetXaxis()->SetLabelSize(0.1);
  ratio->GetYaxis()->SetLabelSize(0.1);
  ratio->GetXaxis()->SetNdivisions(10);
  ratio->GetYaxis()->SetNdivisions(502);


  TLine *line0 = new TLine(low,0,high,0);
  line0->SetLineColor(kBlue);
  line0->Draw();

  TLine *line1 = new TLine(low,2,high,2);
  line1->SetLineColor(kGray);
  line1->SetLineStyle(2);
  line1->Draw();

  TLine *line2 = new TLine(low,-2,high,-2);
  line2->SetLineColor(kGray);
  line2->SetLineStyle(2);
  line2->Draw();

  ratio->Draw("psame");

  ratio->SetMaximum(5);
  ratio->SetMinimum(-5);

  Tcan->cd();
  Tcan->SaveAs(outputDirectory+name+".pdf");
  Tcan->SaveAs(outputDirectory+name+".png");

}
