
// Loop over the ouput (events > fragment > waveforms) of a run from the RawDecoder and produces a plot for each fragment

{

  ////////////////////////////////////////////////////
  char run[100]= "000490_1";  // <--
  int start_event = 1;
  int num_events = 100;        // <--
  
  int num_fragments = 4;
  int num_wav = 6;
  
  int verbose = 1;
  ////////////////////////////////////////////////////

  char filename[100];
  sprintf(filename,"run_%s/RawDecoder_hist_%s.root",run,run);
  cout << filename;

  TFile* f1 = new TFile(filename);
  ssprawdecoder->cd();  //Directory                                                                                                                                                                                                        

  TH1F* hist;
  char histname[100];

  char title[100];
  
  for (int frag=0; frag<num_fragments; ++frag){

    sprintf(title,"Run %s - Fragment %d",run,frag);
    TH1F* hist_transform_fragment = new TH1F("hist_transform_fragment",title,100,0,4);
    hist_transform_fragment->GetXaxis()->SetTitle("MHz");
    
    for (int evt=start_event; evt<=start_event+num_events; ++evt) 
      for (int wav=0; wav<num_wav; ++wav){

   
	sprintf(histname,"ssprawdecoder/evt%d_frag%d_wav%d",evt,frag,wav);
	FFT(histname,hist_transform_fragment,verbose);
	
      }
    
    hist_transform_fragment->SetNormFactor();
    hist_transform_fragment->Draw("hist");
    
    char plotname[100];
    
    sprintf(plotname,"run%s_fragment%d.png",run,frag);
    c1->SaveAs(plotname);
    
  }
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


void FFT(char* h, TH1F* hist_transform_fragment, int verb){
  
  cout << "Histo: "<< histname << endl;
  
  TH1F* hist = (TH1F*)f1->Get(histname);
  if (!hist) return;

  int n_bins = hist->GetNbinsX();
  //cout << "n bins: " << n_bins << endl;
  //TCanvas *c1 = new TCanvas("c1", "FFT", 800 , 400);
  //->Divide(2,1);
  
  //->cd(1);
  
  int nFFT;	
  TH1* hist_transform = 0; // = new TH1F("hist_transform", "FFT", 200, 0., 13.);
  
  //  TVirtualFFT::SetTransform(0);
  hist_transform = hist->FFT(hist_transform, "MAG");
  hist_transform -> Scale (1.0 / float(n_bins));
  
  //  c1->cd(2);
  //	hist_transform  ->SetStats(kFALSE);
  //	hist_transform -> Draw("hist");
  
  nFFT=hist_transform->GetNbinsX();
  //  hist->Draw("");
  //cout << "nFFT: " << nFFT << endl;
  
  Double_t frequency;
  Double_t amplitude;
  
  hist_transform_frequency = new TGraph();
  hist_transform_frequency->SetTitle("Frequency;Frequency [MHz];");
  
  // Loop on the hist_transform to fill the hist_transform_frequency
  for (int k = 2; k <= nFFT/40; ++k){
    frequency =  (k-1)/(n_bins/150.); // MzZ
    amplitude = hist_transform->GetBinContent(k);

    if (verb==2)
      cout << k << ": " << frequency*1000 << " kHz - " << amplitude << endl;  //kHz

    hist_transform_frequency->SetPoint(k,frequency, amplitude);
    hist_transform_fragment ->Fill(frequency, amplitude);
    

  }

  //  if (verb==1) {
    cout << "Dispersion in y: " << hist->GetMaximum() - hist->GetMinimum() << endl;
    cout << "Max frequency: " << findMaxPosition(hist_transform_frequency)*1000 << " kHz";
    
    cout << endl << "Max: "  << TMath::MaxElement(hist_transform_frequency->GetN(),hist_transform_frequency->GetY());
    cout << endl << "Mean: " << hist_transform_frequency->GetMean(2) << " +/- " << hist_transform_frequency->GetRMS(2) << endl;
    
    //}
  //c1->cd(2);
  //  hist_transform_frequency->Draw("AL");
	
  hist_transform->Delete();

}


