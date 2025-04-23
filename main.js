// First, define the base getPokemon function
async function getPokemon(pokemonId) {
    try {
      const response = await fetch(`https://pokeapi.co/api/v2/pokemon/${pokemonId}/`);
      if (!response.ok) {
        throw new Error('Pokémon not found');
      }
      const data = await response.json();
      return data;
    } catch (error) {
      console.error('Error fetching Pokémon:', error);
      return null;
    }
  }
  
  //Function to get multiple Pokémon at once
  async function getMultiplePokemon(ids) {
    const promises = ids.map(id => getPokemon(id));
    console.log("all",promises)
    return Promise.all(promises);
  }
  // 顺序方式 (低效实现)
  async function getMultipleSlow(ids) {
    const results = [];
    for (const id of ids) {
      results.push(await getPokemon(id)); // 关键区别：这里用了await
    }
    return results;
  }
  
  // Function to display Pokémon in the HTML
  async function displayPokemon(pokemonIds) {
    const cardDeck = document.getElementById('card-deck');
    
    // Clear existing cards
    cardDeck.innerHTML = '';
    
    // Get Pokémon data
   const pokemonList = await getMultiplePokemon(pokemonIds);
     //const pokemonList = await getMultipleSlow(pokemonIds);
  
    // Create cards for each Pokémon
    pokemonList.forEach(pokemon => {
      if (!pokemon) return;
      
      const cardWrapper = document.createElement('div');
      cardWrapper.className = 'card-wrapper';
      
      const pokemonCard = document.createElement('div');
      pokemonCard.className = 'pokemon-card';
        const header = document.createElement('div');
    header.className = 'card-header';
      
      
      const img = document.createElement('img');
      img.src = pokemon.sprites.other['official-artwork'].front_default || pokemon.sprites.front_default;
      img.alt = pokemon.name;
      img.loading = 'lazy';
      
      const name = document.createElement('h3');
      name.textContent = pokemon.name.charAt(0).toUpperCase() + pokemon.name.slice(1);
      
      const types = document.createElement('p');
      types.textContent = `Types: ${pokemon.types.map(t => t.type.name).join(', ')}`;
      
      pokemonCard.appendChild(img);
      pokemonCard.appendChild(name);
          pokemonCard.appendChild(header);
  
      pokemonCard.appendChild(types);
      cardWrapper.appendChild(pokemonCard);
      cardDeck.appendChild(cardWrapper);
    });
  }
  
  // Function to initialize the app
  async function initApp() {
    // Example: Display first 9 Pokémon
    const arr = []
    for(let i=0;i<30;i++){
      arr.push(i)
    }
    await displayPokemon(arr);
    
   
  }
  async function getPokemonCombinedData(pokemonId) {
    const endpoints = [
      `https://pokeapi.co/api/v2/pokemon/${pokemonId}/`,        // 基础信息
      `https://pokeapi.co/api/v2/pokemon-species/${pokemonId}/`, // 物种信息
      `https://pokeapi.co/api/v2/ability/${pokemonId}/`,         // 能力信息（可能失败）
      `https://pokeapi.co/api/v2/type/${pokemonId}/`            // 类型信息（可能失败）
    ];
  
    // 使用 allSettled 获取所有端点数据promise4 = Promise.allSettled([promise1, promise2, promise3]);
  
    const results = await Promise.allSettled(
      endpoints.map(url => fetch(url).then(res => {
        if (!res.ok) throw new Error(`HTTP error! status: ${res.status}`);
        console.log(res)
        return res.json();
      }
                                          ))
    );
  
    // 处理结果
    const combinedData = {
      basicInfo: null,
      speciesInfo: null,
      abilityInfo: null,
      typeInfo: null,
      errors: []
    };
  
    results.forEach((result, index) => {
      if (result.status === 'fulfilled') {
        switch(index) {
          case 0: combinedData.basicInfo = result.value; break;
          case 1: combinedData.speciesInfo = result.value; break;
          case 2: combinedData.abilityInfo = result.value; break;
          case 3: combinedData.typeInfo = result.value; break;
        }
      } else {
        combinedData.errors.push({
          endpoint: endpoints[index],
          error: result.reason
        });
      }
    });
  
    return combinedData;
  }
  
  // 使用示例
  async function displayCombinedData() {
    try {
          for (let pokemonId = 190; pokemonId <= 200; pokemonId++) {
  
      const data = await getPokemonCombinedData(pokemonId) // 获取皮卡丘数据
      
      console.log('--- 成功获取的数据 ---');
      if (data.basicInfo) {
        console.log('基础信息:', data.basicInfo.name);
      }
      if (data.speciesInfo) {
        console.log('物种描述:', 
          data.speciesInfo.flavor_text_entries
            .find(entry => entry.language.name === 'en').flavor_text
        );
      }
  }
      console.log('--- 失败的请求---');
      data.errors.forEach(err => {
        console.log(`端点: ${err.endpoint}`);
        console.log(`错误: ${err.error.message}`);
      });
      
    } catch (error) {
      console.error('全局错误:', error);
    }
  }
  
  // 运行示例
  displayCombinedData();

  let promise1 = Promise.resolve(11);

let promise2 = new Promise((resolve, reject) => {
    resolve(22);
});

let promise3 = new Promise((resolve, reject) => {
    setTimeout(() => {
        resolve(33);
    }, 100);
});

let promise4 = Promise.race([promise1, promise2, promise3]);

promise4.then(value => console.log(value));     // 11
  // Start the app when DOM is loaded
  document.addEventListener('DOMContentLoaded', initApp);
