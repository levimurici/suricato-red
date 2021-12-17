FROM nodered/node-red

# Copy package.json to the WORKDIR so npm builds all
# of your added nodes modules for Node-RED
#COPY package.json .
RUN npm install --unsafe-perm --no-update-notifier --no-fund --only=production

# Copy _your_ Node-RED project files into place
# NOTE: This will only work if you DO NOT later mount /data as an external volume.
#       If you need to use an external volume for persistence then
#       copy your settings and flows files to that volume instead.
#COPY settings.js /data/settings.js
#COPY flows_cred.json /data/flows_cred.json
#COPY ./node-red-data/flow1.json /data/flow1.json

# You should add extra nodes via your package.json file but you can also add them here:
WORKDIR /usr/src/node-red
RUN npm install node-red-node-smooth
RUN npm i node-red/node-red-dashboard
#RUN npm install node-red-contrib-aedes
#RUN npm install node-red-contrib-influxdb