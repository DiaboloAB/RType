local player = 2

local matrix = {}

for i = 1, 7 do
    matrix[i] = {}
    for j = 1, 6 do
        matrix[i][j] = 0
    end
end


function push_back(matrix, column, value)
    if column < 1 or column > 7 then
        print("Invalid column")
        return
    end

    for row = 6, 1, -1 do
        if matrix[column][row] == 0 then
            matrix[column][row] = value
            return
        end
    end

    print("Column " .. column .. " is full")
end

function printMatrix(matrix)
    for row = 1, 6 do
        local line = ""
        for col = 1, 7 do
            line = line .. matrix[col][row] .. " "
        end
        print(line)
    end
end

function checkWin()
    for col = 1, 7 do
        for row = 1, 6 do
            local player = matrix[col][row]
            if player ~= 0 then

                if col <= 4 and matrix[col + 1][row] == player and
                   matrix[col + 2][row] == player and matrix[col + 3][row] == player then
                    return 1
                end

                if row <= 3 and matrix[col][row + 1] == player and
                   matrix[col][row + 2] == player and matrix[col][row + 3] == player then
                    return 1
                end

                if col <= 4 and row <= 3 and matrix[col + 1][row + 1] == player and
                   matrix[col + 2][row + 2] == player and matrix[col + 3][row + 3] == player then
                    return 1
                end

                if col <= 4 and row >= 4 and matrix[col + 1][row - 1] == player and
                   matrix[col + 2][row - 2] == player and matrix[col + 3][row - 3] == player then
                    return 1
                end
            end
        end
    end

    return 0
end

function start(registry, gameContext)
    playMusicSound("gameManager", "audio/ambiance.ogg")
end

function update(registry, gameContext)
    if getKeyDown("Escape") then
        exitGame()
    end
end

function exitGame(registry, gameContext)
    exitGame()
end

function events(registry, gameContext)

    if hasEvent("triggerColumn7") then
        push_back(matrix, 7, player)
    end
    if hasEvent("triggerColumn6") then
        push_back(matrix, 6, player)
    end
    if hasEvent("triggerColumn5") then
        push_back(matrix, 5, player)
    end
    if hasEvent("triggerColumn4") then
        push_back(matrix, 4, player)
    end
    if hasEvent("triggerColumn3") then
        push_back(matrix, 3, player)
    end
    if hasEvent("triggerColumn2") then
        push_back(matrix, 2, player)
    end
    if hasEvent("triggerColumn1") then
        push_back(matrix, 1, player)
    end

    if hasEvent("triggerColumn") then
        printMatrix(matrix)
        print("Player " .. player .. " played")
        player = 3 - player
        if player == 1 then
            randColumn = math.random(1, 7)
            entt = instantiate("redBall")
            setEntityPosition(entt, 200 + 115 * (randColumn - 1), 0)
            playMusicSound("gameManager", "audio/luigi-oh-yeah.ogg")
        else
            instantiate("yellowBall")
        end
        if checkWin() == 1 then
            entt = getEntityId("winner")
            if player == 1 then
                setEntityText(entt, "You wins")
                playMusicSound("gameManager", "audio/win.ogg")
            else
                setEntityText(entt, "Luigi win")
                playMusicSound("gameManager", "audio/lose.ogg")
            end
            switchScene("end")
        end

    end
end

function play(registry, gameContext)
    print("Play")
    switchScene("game")
end

