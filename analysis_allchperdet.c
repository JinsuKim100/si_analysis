#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TF1.h>
#include <iostream>

void analysis_allchperdet()
{
    auto file = new TFile("data/RUN511.ch.root","read");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    
    auto tree = (TTree*) file->Get("channels");
    if (!tree) {
        std::cerr << "Error getting TTree" << std::endl;
        file->Close();
        return;
    }

    auto cvs = new TCanvas("cvs", "cvs", 800, 600);
    cvs -> Divide(3,1);

    for (int dch = 1; dch <= 32; ++dch) {
        for(int det=0 ; det < 3 ; det++){
            cvs ->Reset();

            cvs ->cd(det+1);
         

            auto hist = new TH1D("hist", "Histogram with channel in det", 50, 1450, 1600);

            tree->Draw("adc>>hist", "", "");

            auto fit = new TF1("fit", "gaus(0)", 1530, 1600);
            hist->Fit(fit);
        
        }
        
        // Optional: Save each canvas as an image
        cvs->SaveAs("Channel per det.png");
    }
    auto c1 = new TCanvas("c1","c1",800,800);
    c1->Divide(2,2);


    
    file->Close();
}
