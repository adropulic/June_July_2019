#import tensorflow  as tf  
import ROOT as root
import numpy as np
import root_numpy as rootnp
#from tensorflow import keras   
import matplotlib.pyplot as plt
#from sklearn.metrics import roc_curve, auc
#from sklearn.ensemble import RandomForestClassifier
#from sklearn.ensemble import AdaBoostClassifier
#from sklearn.tree import DecisionTreeClassifier
#from sklearn.model_selection import train_test_split

                                                                                                                                                                                    
fVBF = root.TFile.Open("/afs/cern.ch/work/a/addropul/public/forAditya/l1TNtuple-VBF_restrictedeta_060420_recotest.root","READ")
#fVBF.Print()                                                                                                                                                                                                                               
fZB = root.TFile.Open('/afs/cern.ch/work/a/addropul/l1TNtuple-ZeroBias-070520_newmatch.root', "READ")
#fZB.Print()                                                                                                                                                                                                                                
fVBFTree = fVBF.Get("l1NtupleProducer/Stage3Regions/efficiencyTree")
fZBTree = fZB.Get("l1NtupleProducer/Stage3Regions/efficiencyTree")
print(fZBTree.GetEntries())                                                                                                                                                                                                                      
#print(type(fZBTree))                                                                                                                                                                                                                       
#VBF tree to array
fVBFDataDeltaEta = rootnp.tree2array(fVBFTree, branches = 'l1DeltaEta')
fVBFDataDeltaPhi = rootnp.tree2array(fVBFTree, branches = 'l1DeltaPhi')
fVBFDataMass = rootnp.tree2array(fVBFTree, branches = 'l1Mass')
fVBFDataPt1 = rootnp.tree2array(fVBFTree, branches = 'l1Pt_1')
fVBFDataPt2 = rootnp.tree2array(fVBFTree, branches = 'l1Pt_2')


#ZB tree to array
fZBDataDeltaEta = rootnp.tree2array(fZBTree, branches = 'l1DeltaEta')
fZBDataDeltaPhi = rootnp.tree2array(fZBTree, branches = 'l1DeltaPhi')
fZBDataMass = rootnp.tree2array(fZBTree, branches = 'l1Mass')
fZBDataPt1 = rootnp.tree2array(fZBTree, branches = 'l1Pt_1')
fZBDataPt2 = rootnp.tree2array(fZBTree, branches = 'l1Pt_2')

#Applying cut 
import pandas as pd
dataset_VBF = pd.DataFrame({'l1Pt_1':fVBFDataPt1, 'l1Pt_2': fVBFDataPt2,'l1DeltaEta': fVBFDataDeltaEta, 'l1DeltaPhi':fVBFDataDeltaPhi, 'l1Mass':fVBFDataMass})
dataset_VBF = dataset_VBF.drop(dataset_VBF[dataset_VBF.l1Pt_1 < 0].index)
dataset_VBF = dataset_VBF.drop(dataset_VBF[dataset_VBF.l1Pt_2 < 0].index)
dataset_VBF = dataset_VBF.drop(dataset_VBF[dataset_VBF.l1Mass < 0].index)

dataset_ZB = pd.DataFrame({'l1Pt_1':fZBDataPt1, 'l1Pt_2': fZBDataPt2,'l1DeltaEta': fZBDataDeltaEta, 'l1DeltaPhi':fZBDataDeltaPhi, 'l1Mass':fZBDataMass})
dataset_ZB = dataset_ZB.drop(dataset_ZB[dataset_ZB.l1Pt_1 < 0].index)
dataset_ZB = dataset_ZB.drop(dataset_ZB[dataset_ZB.l1Pt_2 < 0].index)
dataset_ZB = dataset_ZB.drop(dataset_ZB[dataset_ZB.l1Mass < 0].index)


dataset_VBF['VBF_label'] = np.ones_like(dataset_VBF['l1Pt_1'].shape[0]).tolist()
dataset_ZB['VBF_label'] = np.zeros_like(dataset_ZB['l1Pt_1'].shape[0]).tolist()

dataset_full = pd.concat([dataset_VBF,dataset_ZB])

x = dataset_full.as_matrix(columns= ['ltP1_1','l1Pt_2','l1DeltaEta','l1DeltaPhi','l1Mass'])

y = dataset_full.as_matrix(columns= ['VBF_label'])
#x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.25, random_state=42)
#
#
##--------------
## BDT 
##--------------
#
#bdt = AdaBoostClassifier(DecisionTreeClassifier(max_depth=1), algorithm="SAMME.R", n_estimators=200)
#       
#
##bdt = RandomForestClassifier(n_estimators=200)
#   
#
##bdt = DecisionTreeClassifier(max_depth = 1)
#
#bdt.fit(x_train,y_train)
#
#y_pred_kerasBDT = bdt.predict_proba(x_test)
#
#y_pred_kerasBDT = np.delete(y_pred_kerasBDT, 0, 1)
#fpr_kerasBDT, tpr_kerasBDT, thresholds_kerasBDT = roc_curve(y_test, y_pred_kerasBDT)
#
#auc_kerasBDT = auc(1-fpr_kerasBDT, tpr_kerasBDT)
#
#
#plt.plot(1 - fpr_kerasBDT, tpr_kerasBDT,label='BDT AUC (area = %0.2f)' % auc_kerasBDT)
##plt.scatter(1 - fpr_keras, tpr_keras)
#plt.xlabel('Signal Efficiency')
#plt.ylabel('Background Rejection')
#plt.title('BDT ROC')
#plt.legend(loc="lower right")
