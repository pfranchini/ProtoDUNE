{

  TFile f1("run_000428_1/RawDecoder_hist_000428_1.root");
  ssprawdecoder->cd();  //Directory
  
  int n_bins = evt1_frag1_wav0->GetNbinsX();
  
  cout << "n bins: " << n_bins << endl;

  TCanvas *c1 = new TCanvas("c1", "FFT", 800 , 400);
  c1->Divide(2,1);

  c1->cd(1);
  evt1_frag1_wav0->Draw("hist");

  TH1 * hist_transform; // = new TH1F("hist_transform", "FFT", 200, 0., 13.);

  TVirtualFFT::SetTransform(0);
  hist_transform = evt1_frag1_wav0-> FFT(hist_transform, "MAG");
  hist_transform -> Scale (1.0 / float(n_bins));

  //  c1->cd(2);
  hist_transform  ->SetStats(kFALSE);
  hist_transform -> Draw("hist");

  nFFT=hist_transform->GetNbinsX();
  
  cout << "nFFT: " << nFFT << endl;
  Double_t frequency;
  Double_t amplitude;

  hist_transform_frequency = new TGraph();
  hist_transform_frequency->SetTitle("Frequency;Frequency [MHz];");

  // Loop on the hist_transform to fill the hist_transform_frequency
  for (int k = 2; k <= nFFT/2; ++k){
    frequency =  (k-1)/(n_bins/150.);
    amplitude = hist_transform->GetBinContent(k);
    cout << k << ": " << frequency*1000 << " kHz - " << amplitude << endl;
    if (amplitude)    hist_transform_frequency->SetPoint(k,frequency, amplitude);

  }
  
  cout << findMaxPosition(hist_transform_frequency)*1000 << " kHz";

  cout << endl << "Max: "  << TMath::MaxElement(hist_transform_frequency->GetN(),hist_transform_frequency->GetY());
  cout << endl << "Mean: " << hist_transform_frequency->GetMean(2) << " +/- " << hist_transform_frequency->GetRMS(2) << endl;
  
  c1->cd(2);
  hist_transform_frequency->Draw("AP*");
  
}

Double_t findMaxPosition(TGraph *G) {
  Double_t x, y;
  G->GetPoint(0, x, y);
  Double_t max_x = x, max_y = y;
  for(int i = 1; i < G->GetN(); i++)
    {
      G->GetPoint(i, x, y);
      if(y > max_y) {
	max_x = x;
	max_y = y;
      }
    }
  return max_x;
}
