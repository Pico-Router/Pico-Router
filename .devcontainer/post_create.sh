mkdir -p third_party/Renode_RP2040/piosim third_party/Renode_RP2040/emulation/bin
ln -sf /opt/piosim/libpiosim.so third_party/Renode_RP2040/piosim/libpiosim.so

dotnet build third_party/Renode_RP2040/emulation/Peripherals.csproj -c Release -p:RenodePath=/opt/renode