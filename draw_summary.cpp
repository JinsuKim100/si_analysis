#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <iostream>

void draw_summary() {
    TFile *file = TFile::Open("data/RUN511.ch.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    TTree *tree = nullptr;
    file->GetObject("channels", tree);
    if (!tree) {
        std::cerr << "Error getting TTree" << std::endl;
        file->Close();
        return;
    }

    TCanvas *cvs = new TCanvas("cvs", "cvs", 1200, 750);
    cvs->Divide(2, 2);

    const char* branches[] = {"adc", "det", "dch"};

    for (int i = 0; i < 3; ++i) {
        std::cout << i << " cvs_" << branches[i] << std::endl;
        cvs->cd(i + 1);
        tree->Draw(branches[i]);
    }

    file->Close();
}
