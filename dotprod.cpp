#include<iostream>
#include<complex>
#include<chrono>
#include<vector>

const int p1npz=2;
const int p1li0=90;
const int p3li0=p1li0;
const int p1lj0=16;
const int p1n_cuts=32; //line 109 of commpart1.c
const int p3lj0=32;
const int p3blockcount=62213;
const int foo=80;

typedef int LO;
typedef long GO;
typedef std::complex<double> CV;
double*** tmpmat;

const CV someCV(10,2);

int main(int argc, char** argv) {
  const std::vector<int> p3mylk0(p1li0, 891); //avg value of the p3->mylk0[0:p1->li0] array

  CV*** densinterpo=new CV**[p1li0];
  for(LO i=0;i<p1li0;i++){
    densinterpo[i]=new CV*[p1lj0];
    for(GO j=0;j<p1lj0;j++){
      densinterpo[i][j]=new CV[p3mylk0[i]];
      for(LO h=0; h<p3mylk0[i]; h++) {
        densinterpo[i][j][h]=someCV;
      }
    }
  }

  CV**** mat_to_plane=new CV***[p3li0];
  for(LO i=0;i<p3li0;i++){
    mat_to_plane[i] = new CV**[p1n_cuts];
    for(LO j=0;j<p1n_cuts;j++){
      mat_to_plane[i][j]=new CV*[p3lj0];
      for(LO k=0;k<p3lj0;k++){
        mat_to_plane[i][j][k]=new CV[p3mylk0[i]];
        for(LO h=0; h<p3mylk0[i]; h++) {
          mat_to_plane[i][j][k][h]=someCV;
        }
      }
    }
  }

  double*** tmpmat = new double**[p3li0];
  for(LO i=0;i<p3li0;i++){
    tmpmat[i]=new double*[p3lj0];
    for(LO j=0;j<p3lj0;j++){
      tmpmat[i][j]=new double[p3mylk0[i]];
      for(LO k=0;k<p3mylk0[i];k++){
        tmpmat[i][j][k]=0.0;
      }
    }
  }

  const auto start = std::chrono::steady_clock::now();

  //allocate
  CV*** loc_data=new CV**[p1li0];
  for(LO i=0;i<p1li0;i++){
    loc_data[i]=new CV*[p3lj0];
    for(LO j=0;j<p3lj0;j++) loc_data[i][j]=new CV[p3mylk0[i]];
  }
  CV tmp1;

  const auto doneAlloc = std::chrono::steady_clock::now();

  //compute
  for(LO i=0;i<p1li0;i++){
    for(LO j=0;j<p1lj0;j++){
      for(LO k=0;k<p3mylk0[i];k++){
        loc_data[i][j][k]= densinterpo[i][j][k];  //FIXME: Here pointer is better      
      }
      if(j>0){
        for(LO k=0;k<p3mylk0[i];k++){
          loc_data[i][p3lj0-j][k]=std::conj(densinterpo[i][j][k]);
        }
      }
    } 
    for(LO j=0;j<p1n_cuts;j++){
      for(LO k=0;k<p3mylk0[i];k++){   
        tmp1=CV(0.0,0.0);
        for(LO h=0;h<p3lj0;h++){
          tmp1+=mat_to_plane[i][j][h][k]*loc_data[i][h][k];
        }       
        tmpmat[i][j][k]+=tmp1.real();
      }
    }     
  }

  for(LO i=0;i<p1li0;i++){
    for(LO j=0;j<p3lj0;j++) delete[] loc_data[i][j];
    delete[] loc_data[i];
  }
  delete[] loc_data;

  const auto doneCompute = std::chrono::steady_clock::now();

  LO* recvcount = new LO[p1npz];
  LO* rdispls = new LO[p1npz];
  double* blocktmp = new double[p3blockcount];

  double** tmp=new double*[p3li0];
  for(LO i=0;i<p3li0;i++){
    //note sure on size of second dimension
    //see https://github.com/SCOREC/wdmapp_coupling/blob/1fa8726657fa356561e015ece53d7a23501eeab4/src/dataprocess.cc#L527-L530 
    //and https://github.com/SCOREC/wdmapp_coupling/issues/95
    tmp[i]=new double[foo]; 
  }

  const auto doneDealloc = std::chrono::steady_clock::now();
  typedef std::chrono::duration<double> TimeS;
  const TimeS allocT = doneAlloc-start;
  const TimeS computeT = doneCompute-doneAlloc;
  const TimeS deallocT = doneDealloc-doneCompute;
  const TimeS total = allocT+computeT+deallocT;
  printf("alloc(s) compute(s) dealloc(s) total(s) %.5f %.5f %.5f %.5f\n",
      allocT.count(), computeT.count(), deallocT.count(), total.count());
  return 0;
}
