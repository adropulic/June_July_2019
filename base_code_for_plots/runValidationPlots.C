{
  gROOT->ProcessLine(".L ~/Documents/work/Analysis/PhaseIIStudies/2018_L1TMTD/comparisonPlots.C");

  TString treePath = "L1MTDAnalyzer/L1TauTree";
  TString inputDirectory  = "phase2-Mar23/dyll.root";
  TString outputDirectory = "~/Dropbox/3_22_19/validationPlots/";
  comparisonPlots("l1Pt","genPt>20","genPt<5",treePath, inputDirectory, outputDirectory, "l1Pt",100,0,100);
  comparisonPlots("l1Eta","genPt>20","genPt<5",treePath, inputDirectory, outputDirectory, "l1Eta",100,-4,4);
  comparisonPlots("l1DecayMode","genPt>20","genPt<5",treePath, inputDirectory, outputDirectory, "l1DM",11,0,11);
  comparisonPlots("track1PVDZ","genPt>20","genPt<5",treePath, inputDirectory, outputDirectory, "l1track1PVDZ",100,-5,5);
  comparisonPlots("track2PVDZ","genPt>20","genPt<5",treePath, inputDirectory, outputDirectory, "l1track2PVDZ",100,-5,5);

  comparisonPlots("track1Time","genPt>20","genPt<5",treePath, inputDirectory, outputDirectory, "track1Time",100,0,22);

  comparisonPlots("zVTX","genPt>20","genPt<5",treePath, inputDirectory, outputDirectory, "zVTX",100,-10,10);
  comparisonPlots("track1ChiSquared","genPt>20","genPt<5",treePath, inputDirectory, outputDirectory, "track1ChiSquared",100,0,100);
  //l1Iso has the tau included in the sum so it must be removed
  comparisonPlots("l1Iso-l1Pt","genPt>20","genPt<5",treePath, inputDirectory, outputDirectory, "l1Iso",60,0,60);  
 comparisonPlots("tauL1StripDR","genPt>20","genPt<5",treePath, inputDirectory, outputDirectory, "tauL1StripDR",50,0,5);
}
