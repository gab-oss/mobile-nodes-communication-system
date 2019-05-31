import docker
import random
import time

client = docker.from_env()
containers = client.containers.list()
client.networks.prune()

#disconnect from default network
for network in client.networks.list():
    if set(network.containers) & set(containers):
        for container in containers:
            network.disconnect(container)
        break

#create networks
networks = []
for i in range(3):
    networks.append(client.networks.create("net"+repr(i), driver="bridge"))

#swapping connections
try:
    while True:
        time.sleep(1)
        network = random.choice(networks)
        network.reload()
        if random.choice([True, False]):
            unconnectedContainers = list(set(containers) - set(network.containers))
            if not unconnectedContainers:
                continue
            container = random.choice(unconnectedContainers)
            if container:
                network.connect(container)
                print("Connected " + container.name + " to " + network.name)
        elif network.containers:
            container = random.choice(network.containers)
            if container:
                network.disconnect(container)
                print("Disconnected " + container.name + " from " + network.name)

except KeyboardInterrupt:
    print("ending swapping")

client.networks.prune()