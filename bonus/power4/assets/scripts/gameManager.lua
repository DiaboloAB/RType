function load(registry, gameContext)
    print("Game Manager Loaded")
    playMusicSound("gameManager", "audio/ambiance.ogg")
end

function update(registry, gameContext)
    if getKeyDown("H") then
        print("HellowWorld")
    end
end

function exitGame(registry, gameContext)
    exitGame()
end